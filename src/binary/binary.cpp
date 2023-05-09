#include <fcntl.h>
#include <sys/mman.h>
#include <binary/binaryTrie.hpp>
#include <binary/binary.hpp>
#include <fstream>
#include <index/index.hpp>
#include <unordered_map>

using namespace std;

BinaryBuffer write_docs_section(
    indexBuilder& index,
    unordered_map<size_t, uint32_t>& doc_offset) {
  BinaryBuffer buffer;
  const auto docs = index.getDocs();
  const uint32_t docs_size = docs.size();
  buffer.write(&docs_size, sizeof(docs_size));
  for (size_t i = 0; i < docs.size(); i++) {
    doc_offset[docs[i].first] = buffer.size();
    const uint8_t doc_size = docs[i].second.size() + 1;
    buffer.write(&doc_size, sizeof(doc_size));
    buffer.write(docs[i].second.data(), doc_size - 1);
  }
  return buffer;
}

void serialize(
    Node* node,
    BinaryBuffer& buffer,
    unordered_map<Node*, Offsets>& node_to_offsets) {
  const uint32_t children_count = node->children_.size();
  buffer.write(&children_count, sizeof(children_count));
  for (const auto& child : node->children_) {
    const uint8_t letter = child.first;
    buffer.write(&letter, sizeof(letter));
  }
  for (size_t i = 0; i < children_count; ++i) {
    const uint32_t child_offset = 0xffffffff;
    buffer.write(&child_offset, sizeof(child_offset));
  }
  buffer.write(&node->is_leaf_, sizeof(node->is_leaf_));
  if (node->is_leaf_ == 1) {
    buffer.write(&node->entry_offset_, sizeof(node->entry_offset_));
  }
  for (const auto& child : node->children_) {
    node_to_offsets[child.second.get()].self_offset = buffer.size();
    node_to_offsets[node].children_offsets.push_back(buffer.size());
    serialize(child.second.get(), buffer, node_to_offsets);
  }
}

static void update_child_offsets(
    BinaryBuffer& buffer,
    unordered_map<Node*, Offsets>& node_to_offsets) {
  for (const auto& [node, offsets] : node_to_offsets) {
    size_t write_offset = offsets.self_offset + 4 + node->children_.size();
    for (const auto& child_offset : offsets.children_offsets) {
      buffer.write_to(&child_offset, sizeof(child_offset), write_offset);
      write_offset += sizeof(child_offset);
    }
  }
}

BinaryBuffer write_dictionary_section(
    indexBuilder& index,
    vector<uint32_t>& entry_offset) {
  BinaryBuffer buffer;
  Trie trie;
  size_t iter = 0;
  auto entries = index.getIndexes();
  for (size_t i = 0; i < entries.size(); i++) {
    const auto terms = entries[i].getEntries().second;
    for (size_t j = 0; j < terms.size(); j++) {
      trie.insert(terms[j].text, entry_offset[iter]);
      iter++;
    }
  }
  unordered_map<Node*, Offsets> node_to_offsets;
  serialize(trie.root(), buffer, node_to_offsets);
  update_child_offsets(buffer, node_to_offsets);
  return buffer;
}

BinaryBuffer write_entries_section(
    indexBuilder& index,
    unordered_map<size_t, uint32_t>& doc_offset,
    vector<uint32_t>& entry_offset) {
  BinaryBuffer buffer;
  entry_offset.push_back(0);
  auto entries = index.getIndexes();
  for (size_t i = 0; i < entries.size(); i++) {
    const auto terms = entries[i].getEntries().second;
    for (size_t j = 0; j < terms.size(); j++) {
      const uint32_t doc_count = terms[j].doc_count;
      buffer.write(&doc_count, sizeof(doc_count));
      auto docIdAndPos = terms[j].doc_id_and_pos;
      for (size_t k = 0; k < docIdAndPos.size(); k++) {
        const uint32_t pos_count = docIdAndPos[k].second.size();
        buffer.write(
            &doc_offset[docIdAndPos[k].first],
            sizeof(doc_offset[docIdAndPos[k].first]));
        buffer.write(&pos_count, sizeof(pos_count));
        for (size_t l = 0; l < pos_count; l++) {
          const uint32_t pos = docIdAndPos[k].second[l];
          buffer.write(&pos, sizeof(pos));
        }
      }
      entry_offset.push_back(buffer.size());
    }
  }
  return buffer;
}

BinaryBuffer write_header_section() {
  BinaryBuffer buffer;
  const uint8_t section_count = 3;
  buffer.write(&section_count, sizeof(section_count));
  vector<string> section_name = {"dictionary", "entries", "docs"};
  for (const auto& section : section_name) {
    const uint8_t section_size = section.size() + 1;
    buffer.write(&section_size, sizeof(section_size));
    buffer.write(section.data(), section_size - 1);
    const uint32_t section_offset = 3;
    buffer.write(&section_offset, sizeof(section_offset));
  }
  return buffer;
}

void BinaryBuffer::write(const void* data, size_t size) {
  const auto* data_start_address = static_cast<const char*>(data);
  copy(data_start_address, data_start_address + size, back_inserter(data_));
}

void BinaryBuffer::write_to(const void* data, size_t size, size_t offset) {
  const auto* data_start_address = static_cast<const char*>(data);
  auto offset_iter = data_.begin();
  advance(offset_iter, offset);
  copy(data_start_address, data_start_address + size, offset_iter);
}

void BinaryBuffer::write_to_file(ofstream& file) const {
  file.write(data_.data(), static_cast<streamsize>(data_.size()));
}

void BinaryReader::read(void* dest, size_t size) {
  auto* dest_start_address = static_cast<char*>(dest);
  copy(current_, current_ + size, dest_start_address);
  current_ += size;
}

BinaryData::BinaryData(const filesystem::path& index_path) {
  int file = open((index_path / "bindex").c_str(), O_RDONLY);
  size_ = filesystem::file_size(index_path / "bindex");
  data_ =
      static_cast<char*>(mmap(nullptr, size_, PROT_READ, MAP_PRIVATE, file, 0));
}

BinaryData::~BinaryData() {
  munmap(data_, size_);
}