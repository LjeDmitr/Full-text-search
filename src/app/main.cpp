#include <index/index.hpp>
#include <iostream>

using namespace std;

int main() {
  indexBuilder index_builder;
  index_builder.add_document("199903", "The Matrix");
  index_builder.add_document("200305", "The Matrix Reloaded");
  index_builder.add_document("200311", "The Matrix Revolutions");
  for (const auto& index : index_builder.getIndexes()) {
    textIndexWriter::write("index", index);
  }
  return 0;
}