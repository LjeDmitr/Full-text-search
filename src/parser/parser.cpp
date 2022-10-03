#include <parser/parser.hpp>
#include <vector>
#include <cctype> 

using namespace std;

static string deletePunct(string text) {
	for (int i = 0; i < (int)text.size() - 1; ++i) {
		if (ispunct(text[i])) {
			text.erase(i, 1);
		} 
	}
	return text;
}

static string stringToLower(string text) {
	for (int i = 0; i < (int)text.size() - 1; ++i) {
		text[i] = (char)tolower(text[i]);
	}
	return text;
}

static vector<string> splitWords(string text, vector<string> vector) {
	int pos = 0;
	for (int i = 0; i < (int)text.size() - 1; ++i) {
		if (isspace(text[i])) {
			if (i == pos) {
				pos++;
				break;
			}
			vector.push_back(text.substr(pos, i - pos));
			pos = i + 1;
		}
	}
	if (isspace(text[pos]) == 0) {
		vector.push_back(text.substr(pos));
	}
	return vector;
}

static vector<string> deleteStopWords(string stop_words[], vector<string> vector) {
	auto iter = vector.cbegin();
	for (int i = 0; i < (int)vector.size(); ++i) {
		for (int j = 0; j < (int)stop_words->size(); ++j) {
			if (vector[i] == stop_words[j]) {
				vector.erase(iter + i);
			}
		}
	}
	return vector;
}

static string generateNgrams(vector<string> vector, int min_ngram_length, int max_ngram_length) {
    string result;
	for (int i = 0; i < (int)vector.size(); ++i) {
		for (int j = min_ngram_length; j <= max_ngram_length && j <= (int)vector[i].size(); ++j) {
            result += vector[i].substr(0, j) + " " + to_string(i) + " ";
		}
	}
	result.erase(result.size() - 1);
    return result;
}

string parseStr(string text, string stop_words[], int ngram_min_length, int ngram_max_length) {
	text = deletePunct(text);
	text = stringToLower(text);
	vector<string> words;
	words = splitWords(text, words);
	words = deleteStopWords(stop_words, words);
	string result = generateNgrams(words, ngram_min_length, ngram_max_length);
    return result;
}