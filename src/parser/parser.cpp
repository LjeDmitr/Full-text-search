#include <cctype>
#include <parser/parser.hpp>

using namespace std;

std::vector<std::string> stop_words = {
    "a",     "an",    "and",  "are",  "as", "at",   "be",   "but",   "by",
    "for",   "if",    "in",   "into", "is", "it",   "no",   "not",   "of",
    "on",    "or",    "s",    "such", "t",  "that", "the",  "their", "then",
    "there", "these", "they", "this", "to", "was",  "will", "with"};

static string deletePunct(string text) {
  for (size_t i = 0; i < text.size(); ++i) {
    if (ispunct(text[i])) {
      text.erase(i, 1);
    }
  }
  return text;
}

static string stringToLower(string text) {
  for (size_t i = 0; i < text.size(); ++i) {
    text[i] = (char)tolower(text[i]);
  }
  return text;
}

static vector<string> splitWords(string text, vector<string> words) {
  size_t pos = 0;
  for (size_t i = 0; i < text.size(); ++i) {
    if (isspace(text[i])) {
      if (i == pos) {
        pos++;
      } else {
        words.push_back(text.substr(pos, i - pos));
        pos = i + 1;
      }
    }
  }
  if (isspace(text[pos]) == 0 && pos < text.size()) {
    words.push_back(text.substr(pos));
  }
  return words;
}

static vector<string> deleteStopWords(vector<string> words) {
  auto iter = words.cbegin();
  for (size_t i = 0; i < words.size(); ++i) {
    for (size_t j = 0; j < stop_words.size(); ++j) {
      if (words[i] == stop_words[j]) {
        words.erase(iter + i);
      }
    }
  }
  return words;
}

static vector<pair<string, vector<int>>> generateNgrams(
    vector<string> words,
    int min_ngram_length,
    int max_ngram_length) {
  vector<pair<string, vector<int>>> ngrams;
  vector<pair<string, vector<int>>>::iterator iter;
  int count_pos = 0;
  bool check_ngrams = false, check_iter = false;
  for (size_t i = 0; i < words.size(); ++i) {
    for (int j = min_ngram_length;
         j <= max_ngram_length && j <= (int)words[i].size();
         ++j) {
      iter = ngrams.begin();
      for (size_t k = 0; k < ngrams.size(); k++, iter++) {
        if (ngrams[k].first == words[i].substr(0, j)) {
          check_iter = true;
          break;
        }
      }
      if (!check_iter) {
        iter = ngrams.end();
      }
      if (iter == ngrams.end()) {
        vector<int> new_vector = {count_pos};
        ngrams.push_back(make_pair(words[i].substr(0, j), new_vector));
        check_ngrams = true;
      } else {
        iter->second.push_back(count_pos);
        check_ngrams = true;
      }
    }
    if (check_ngrams) {
      ++count_pos;
      check_ngrams = false;
    }
  }
  return ngrams;
}

static string makeParsingStr(vector<pair<string, vector<int>>> ngrams) {
  string result;
  for (size_t i = 0; i < ngrams.size(); ++i) {
    result += ngrams[i].first + " ";
    for (size_t j = 0; j < ngrams[i].second.size(); ++j) {
      result += to_string(ngrams[i].second[j]) + " ";
    }
  }
  if (!result.empty()) {
    result.erase(result.size() - 1);
  }
  return result;
}

void parser::parseStr(string text, int ngram_min_length, int ngram_max_length) {
  text = deletePunct(text);
  text = stringToLower(text);
  vector<string> words;
  words = splitWords(text, words);
  words = deleteStopWords(words);
  ngrams = generateNgrams(words, ngram_min_length, ngram_max_length);
  parsing_str = makeParsingStr(ngrams);
}

string parser::getParsingStr() {
  return parsing_str;
}

vector<pair<string, vector<int>>> parser::getNgrams() {
  return ngrams;
}