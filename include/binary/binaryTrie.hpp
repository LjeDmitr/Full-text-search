#pragma once
#include <iostream>
#include <map>
#include <memory>

struct Node {
  std::map<char, std::unique_ptr<Node>> children_;
  std::uint32_t entry_offset_ = 0;
  std::uint8_t is_leaf_ = 0;
};

class Trie {
 private:
  Node root_;

 public:
  void insert(const std::string& word, std::uint32_t entry_offset);
  Node* root() {
    return &root_;
  }
};