#include <fcntl.h>
#include <sys/mman.h>
#include <binary/binaruTrie.hpp>
#include <binary/binary.hpp>
#include <fstream>
#include <index/index.hpp>
#include <unordered_map>

using namespace std;

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