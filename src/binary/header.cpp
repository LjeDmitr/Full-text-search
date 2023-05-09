#include <binary/binary.hpp>
#include <binary/header.hpp>

using namespace std;

Header::Header(const char* data) {
  BinaryReader reader(data);
  reader.read(&section_count_, sizeof(section_count_));
  for (std::size_t i = 0; i < section_count_; ++i) {
    std::uint8_t length = 0;
    reader.read(&length, sizeof(length));
    std::string name(length - 1, ' ');
    reader.read(name.data(), name.length());
    std::uint32_t section_offset = 0;
    reader.read(&section_offset, sizeof(section_offset));
    sections_[name] = section_offset;
  }
}

uint32_t Header::section_offset(const string& name) const {
  const auto offset = sections_.find(name);
  return offset->second;
}