#include <binary/binaryTrie.hpp>

using namespace std;

void Trie::insert(const string &word, uint32_t entry_offset) {
    Node *current = &root_;
    for (const auto &symbol : word) {
        if (current->children_.find(symbol) == current->children_.end()) {
            current->children_[symbol] = make_unique<Node>();
        }
        current = current->children_[symbol].get();
    }
    current->entry_offset_ = entry_offset;
    if ((current->is_leaf_ == 0) && (current != &root_)) {
        current->is_leaf_ = 1;
    }
}