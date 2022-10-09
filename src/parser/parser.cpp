#include <parser/parser.hpp>
#include <cctype> 

using namespace std;

string deletePunct(string text) {
	for (int i = 0; i < (int)text.size(); ++i) {
		if (ispunct(text[i])) {
			text.erase(i, 1);
		}
	}
	return text;
}

string stringToLower(string text) {
	for (int i = 0; i < (int)text.size(); ++i) {
		text[i] = (char)tolower(text[i]);
	}
	return text;
}

vector<string> splitWords(string text, vector<string> vector) {
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

vector<string> deleteStopWords(vector<string> stop_words, vector<string> words) {
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

string generateNgrams(vector<string> vector, int min_ngram_length, int max_ngram_length) {
    string result;
	for (int i = 0; i < (int)vector.size(); ++i) {
		for (int j = min_ngram_length; j <= max_ngram_length && j <= (int)vector[i].size(); ++j) {
            result += vector[i].substr(0, j) + " " + to_string(i) + " ";
		}
	}
	if (!result.empty()) {
		result.erase(result.size() - 1);
	}
    return result;
}

string parseStr(string text, vector<string> stop_words, int ngram_min_length, int ngram_max_length) {
	text = deletePunct(text);
	text = stringToLower(text);
	vector<string> words;
	words = splitWords(text, words);
	words = deleteStopWords(stop_words, words);
	string result = generateNgrams(words, ngram_min_length, ngram_max_length);
    return result;
}