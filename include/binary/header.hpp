#pragma once
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

class Header {
 private:
  std::uint8_t section_count_;
  std::unordered_map<std::string, std::uint32_t> sections_;

 public:
  explicit Header(const char* data);
  std::uint8_t section_count() const {
    return section_count_;
  }
  std::uint32_t section_offset(const std::string& name) const;
};