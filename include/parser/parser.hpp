#pragma once

string deletPunct(string text);
string stringToLower(string text);
vector<string> splitWords(string text, vector<string> vector);
vector<string> deleteStopWords(string stop_words[], vector<string> vector);
void generateNgrams(vector<string> vector, int min_ngram_length, int max_ngram_length);