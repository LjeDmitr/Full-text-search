#pragma once
#include <iostream>
#include <string>
#include <vector>

struct search_info {
  int df;
  std::vector<std::pair<size_t, double>> tf;
};

class SearchIndex {
 private:
  std::vector<std::pair<std::string, double>> search_result;
  void score(
      BinaryIndexAccessor accessor,
      double N,
      std::vector<search_info> querys_info,
      size_t doc_id);

 public:
  void search(std::string str, std::string path_index);
  std::vector<std::pair<std::string, double>> getSearchResult();
};
