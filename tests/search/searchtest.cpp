#include <gtest/gtest.h>
#include <index/index.hpp>
#include <search/search.hpp>

using namespace std;

TEST(search, bye_earth) {
  indexBuilder index_builder;
  index_builder.add_document(100, "Hello World");
  index_builder.add_document(101, "Bye World");
  index_builder.add_document(102, "Hello Earth");
  BinaryIndexWriter::write("index", index_builder);
  
  SearchIndex index_search;
  index_search.search("bye earth", "index/");
  vector<pair<string, double>> result = index_search.getSearchResult();
  vector<double> expect = {3.295836, 1.098612};
  ASSERT_EQ(expect.size(), result.size());
  for (size_t i = 0; i < expect.size(); i++) {
    ASSERT_NEAR(expect[i], result[i].second, 1e-6);
  }
}

TEST(search, hello_world) {
  indexBuilder index_builder;
  index_builder.add_document(100, "Hello World");
  index_builder.add_document(101, "Bye World");
  index_builder.add_document(102, "Hello Earth");
  BinaryIndexWriter::write("index", index_builder);

  SearchIndex index_search;
  index_search.search("hello world", "index/");
  vector<pair<string, double>> result = index_search.getSearchResult();
  vector<double> expect = {2.432790, 1.216395, 1.216395};
  ASSERT_EQ(expect.size(), result.size());
  for (size_t i = 0; i < expect.size(); i++) {
    ASSERT_NEAR(expect[i], result[i].second, 1e-6);
  }
}