#pragma once
#include <filesystem>
#include <iostream>
#include <vector>
#include <binary/binaryTrie.hpp>
#include <unordered_map>
#include <index/index.hpp>

struct Offsets {
  uint32_t self_offset = 0;
  std::vector<uint32_t> children_offsets;
};

class BinaryReader {
 private:
  const char* data_;
  const char* current_;

 public:
  explicit BinaryReader(const char* buf) : data_(buf), current_(buf) {
  }
  void read(void* dest, std::size_t size);
  const char* current() const {
    return current_;
  }
  void move(std::size_t size) {
    current_ += size;
  }
  void move_back_to_start() {
    current_ = data_;
  }
};

class BinaryData {
 private:
  char* data_;
  std::size_t size_;

 public:
  explicit BinaryData(const std::filesystem::path& index_dir);
  ~BinaryData();
  char* data() const {
    return data_;
  }
  std::size_t size() const {
    return size_;
  }
};

class BinaryBuffer {
 private:
  std::vector<char> data_;

 public:
  void write(const void* data, std::size_t size);
  void write_to(const void* data, std::size_t size, std::size_t offset);
  void write_to_file(std::ofstream& file) const;
  std::size_t size() const {
    return data_.size();
  }
};

void serialize(
    Node* node,
    BinaryBuffer& buffer,
    std::unordered_map<Node*, Offsets>& node_to_offsets);

BinaryBuffer write_docs_section(
    indexBuilder& index,
    std::unordered_map<std::size_t, uint32_t>& doc_offset);

BinaryBuffer write_dictionary_section(
    indexBuilder& index,
    std::vector<uint32_t>& entry_offset);

BinaryBuffer write_entries_section(
    indexBuilder& index,
    std::unordered_map<std::size_t, uint32_t>& doc_offset,
    std::vector<uint32_t>& entry_offset);

BinaryBuffer write_header_section();