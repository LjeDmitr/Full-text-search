#pragma once
#include <iostream>
#include <map>
#include <vector>

class Entries {
 private:
  const char* data_;

 public:
  explicit Entries(const char* data) : data_(data) {
  }
  std::map<std::size_t, std::vector<std::size_t>> get_term_infos(
      std::uint32_t entry_offset);
};