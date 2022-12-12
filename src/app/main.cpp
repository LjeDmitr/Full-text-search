#include <index/index.hpp>
#include <search/search.hpp>
#include <iostream>

using namespace std;

int main() {
  indexBuilder index_builder;
  index_builder.add_document("100", "Hello World");
  index_builder.add_document("101", "Bye World");
  index_builder.add_document("102", "Hello Earth");
  vector<Index> indexes = index_builder.getIndexes();
  for (size_t i = 0; i < indexes.size(); ++i) {
    textIndexWriter::write("index", indexes[i]);
  }
  SearchIndex obj;
  obj.search("bye earth", "index/entries/");
  obj.score("100");
  obj.score("101");
  obj.score("102");
  cout << "id\t score\t text" << endl;
  for (const auto& result : obj.getSearchResult()) {
    cout << result.first + "\t " << result.second << "\t " << endl;
  }
  return 0;
}