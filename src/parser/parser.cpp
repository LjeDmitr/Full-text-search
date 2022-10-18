#include <parser/parser.hpp>
#include <cctype> 

using namespace std;

std::vector<std::string> stop_words = {"a", "an", "and", "are", "as", "at", "be", "but", "by", "for", "if", "in", "into", "is", "it", "no", "not", "of", "on", "or", "s", "such", "t", "that", "the", "their", "then", "there", "these", "they", "this", "to", "was", "will", "with"}; 

static string deletePunct(string text) {
	for (int i = 0; i < (int)text.size(); ++i) {
		if (ispunct(text[i])) {
			text.erase(i, 1);
		}
	}
	return text;
}

static string stringToLower(string text) {
	for (int i = 0; i < (int)text.size(); ++i) {
		text[i] = (char)tolower(text[i]);
	}
	return text;
}

static vector<string> splitWords(string text, vector<string> words) {
	int pos = 0;
	for (int i = 0; i < (int)text.size(); ++i) {
		if (isspace(text[i])) {
			if (i == pos) {
				pos++;
			} else {
				words.push_back(text.substr(pos, i - pos));
				pos = i + 1;
			}
		}
	}
	if (isspace(text[pos]) == 0 && pos < (int)text.size()) {
		words.push_back(text.substr(pos));
	}
	return words;
}

static vector<string> deleteStopWords(vector<string> words) {
	auto iter = words.cbegin();
	for (int i = 0; i < (int)words.size(); ++i) {
		for (int j = 0; j < (int)stop_words.size(); ++j) {
			if (words[i] == stop_words[j]) {
				words.erase(iter + i);
			}
		}
	}
	return words;
}

static vector<pair<string, int>> generateNgrams(vector<string> words, int min_ngram_length, int max_ngram_length) {
	vector<pair<string, int>> ngrams;
	int count_number = 0;
	bool check_ngrams = false;
	for (int i = 0; i < (int)words.size(); ++i) {
		for (int j = min_ngram_length; j <= max_ngram_length && j <= (int)words[i].size(); ++j) {
            ngrams.push_back(make_pair(words[i].substr(0, j), count_number));
			check_ngrams = true;
		}
		if (check_ngrams) {
			++count_number;
			check_ngrams = false;
		}
	}
    return ngrams;
}

static string makeParsingStr(vector<pair<string, int>> ngrams) {
 	string result;
	for (int i = 0; i < (int)ngrams.size(); ++i) {
        result += ngrams[i].first + " " + to_string(ngrams[i].second) + " ";
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

vector<pair<string, int>> parser::getNgrams() {
	return ngrams;
}