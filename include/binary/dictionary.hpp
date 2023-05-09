#pragma once
#include <binary/binaryTrie.hpp>

class Dictionary {
 private:
  const char* data_;

 public:
  explicit Dictionary(const char* data) : data_(data) {
  }
  std::uint32_t retrieve(const std::string& word);
};