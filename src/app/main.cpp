#include <index/index.hpp>
#include <iostream>

using namespace std;

int main() {
  indexBuilder index_builder;
  index_builder.add_document("199903", "The Matrix");
  index_builder.add_document("200305", "The Matrix Reloaded");
  index_builder.add_document("200311", "The Matrix Revolutions");
  vector<Index> indexes = index_builder.getIndexes();
  for (size_t i = 0; i < indexes.size(); ++i) {
    textIndexWriter::write("index", indexes[i]);
  }
  return 0;
}