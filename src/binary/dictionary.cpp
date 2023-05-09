#include <binary/binary.hpp>
#include <binary/dictionary.hpp>

using namespace std;

uint32_t Dictionary::retrieve(const string& word) {
  BinaryReader reader(data_);
  uint32_t children_count = 0;
  uint8_t is_leaf = 0;
  uint32_t entry_offset = 0;

  for (const auto& symbol : word) {
    uint32_t child_offset = 0;
    reader.read(&children_count, sizeof(children_count));
    size_t child_pos = children_count;
    for (size_t i = 0; i < children_count; ++i) {
      uint8_t letter = 0;
      reader.read(&letter, sizeof(letter));
      if (letter == symbol) {
        child_pos = i;
      }
    }
    if (child_pos == children_count) {
      cout << "failed to get a list of document IDs for the specified term"
           << word << endl;
      exit(-1);
    }
    reader.move(sizeof(child_offset) * child_pos);
    reader.read(&child_offset, sizeof(child_offset));
    reader.move(sizeof(child_offset) * (children_count - child_pos - 1));
    reader.read(&is_leaf, sizeof(is_leaf));
    if (is_leaf == 1) {
      reader.read(&entry_offset, sizeof(entry_offset));
    }
    if (child_offset != 0) {
      reader.move_back_to_start();
      reader.move(child_offset);
    }
  }

  reader.read(&children_count, sizeof(children_count));
  reader.move(static_cast<size_t>(children_count * 5));
  reader.read(&is_leaf, sizeof(is_leaf));
  reader.read(&entry_offset, sizeof(entry_offset));
  return entry_offset;
}