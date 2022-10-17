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

static vector<string> splitWords(string text, vector<string> vector) {
	int pos = 0;
	for (int i = 0; i < (int)text.size(); ++i) {
		if (isspace(text[i])) {
			if (i == pos) {
				pos++;
			} else {
				vector.push_back(text.substr(pos, i - pos));
				pos = i + 1;
			}
		}
	}
	if (isspace(text[pos]) == 0 && pos < (int)text.size()) {
		vector.push_back(text.substr(pos));
	}
	return vector;
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

static string generateNgrams(vector<string> vector, int min_ngram_length, int max_ngram_length) {
    string result;
	int count_number = 0;
	bool check_word = false;
	for (int i = 0; i < (int)vector.size(); ++i) {
		for (int j = min_ngram_length; j <= max_ngram_length && j <= (int)vector[i].size(); ++j) {
            result += vector[i].substr(0, j) + " " + to_string(count_number) + " ";
			check_word = true;
		}
		if (check_word) {
			++count_number;
			check_word = false;
		}
	}
	if (!result.empty()) {
		result.erase(result.size() - 1);
	}
    return result;
}

string parseStr(string text, int ngram_min_length, int ngram_max_length) {
	text = deletePunct(text);
	text = stringToLower(text);
	vector<string> words;
	words = splitWords(text, words);
	words = deleteStopWords(words);
	string result = generateNgrams(words, ngram_min_length, ngram_max_length);
    return result;
}