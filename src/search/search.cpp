#include <dirent.h>
#include <algorithm>
#include <binary/binary.hpp>
#include <cmath>
#include <parser/parser.hpp>
#include <search/search.hpp>
#include <set>

using namespace std;

static int termFrequency(vector<pair<size_t, double>> query_tf, size_t doc_id) {
  for (size_t i = 0; i < query_tf.size(); i++) {
    if (query_tf[i].first == doc_id) {
      return query_tf[i].second;
    }
  }
  return 0;
}

void SearchIndex::score(
    BinaryIndexAccessor accessor,
    double N,
    vector<search_info> querys_info,
    size_t doc_id) {
  double score = 0.0, idf = 0.0;
  for (size_t i = 0; i < querys_info.size(); i++) {
    idf = (double)N / querys_info[i].df;
    score += termFrequency(querys_info[i].tf, doc_id) * log(idf);
  }
  if (score != 0) {
    search_result.push_back(
        make_pair(accessor.get_document_by_id(doc_id), score));
  }
}

void SearchIndex::search(string str, string indexPath) {
  parser parsing_string;
  BinaryData index(indexPath);
  Header header(index.data());
  BinaryIndexAccessor accessor(index.data(), header);
  parsing_string.parseStr(str);
  vector<pair<string, vector<int>>> ngrams = parsing_string.getNgrams();
  double total_doc_count = static_cast<double>(accessor.get_document_count());
  vector<search_info> querys_info;
  set<size_t> findDocsList;
  for (size_t i = 0; i < ngrams.size(); i++) {
    vector<size_t> docList = accessor.get_documents_by_term(ngrams[i].first);
    size_t df = docList.size();
    struct search_info ngram;
    ngram.df = df;
    for (size_t j = 0; j < df; j++) {
      ngram.tf.push_back(make_pair(
          docList[j],
          static_cast<double>(
              accessor
                  .get_term_positions_in_document(ngrams[i].first, docList[j])
                  .size())));
      findDocsList.insert(docList[j]);
    }
    querys_info.push_back(ngram);
  }

  set<size_t>::iterator it = findDocsList.begin();
  for (size_t i = 0; it != findDocsList.end(); i++, it++) {
    score(accessor, total_doc_count, querys_info, *it);
  }
}

vector<pair<string, double>> SearchIndex::getSearchResult() {
  sort(
      search_result.begin(),
      search_result.end(),
      [](const auto& x, const auto& y) { return x.second > y.second; });
  return search_result;
}
