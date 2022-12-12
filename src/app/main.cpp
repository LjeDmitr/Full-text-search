#include <index/index.hpp>
#include <iostream>
#include <search/search.hpp>

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
  SearchIndex index_search;
  index_search.search("hello world", "index/");
  index_search.score("100");
  index_search.score("101");
  index_search.score("102");
  cout << "id" << setw(12) << "score" << setw(12) << "text" << endl;
  IndexAccessor index_access;
  vector<pair<string, double>> result = index_search.getSearchResult();
  for (size_t i = 0; i < result.size(); i++) {
    index_access.readDoc(result[i].first);
    cout << result[i].first << setw(12) << result[i].second << setw(16)
         << index_access.getDocText() << endl;
  }
  return 0;
}