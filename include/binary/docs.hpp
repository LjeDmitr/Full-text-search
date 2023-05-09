#pragma once
#include <iostream>

class Documents {
 private:
  const char* data_;

 public:
  explicit Documents(const char* data) : data_(data) {
  }
  std::string get_document_by_id(std::size_t identifier) const;
  std::size_t get_document_count() const;
};