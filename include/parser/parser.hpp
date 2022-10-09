#pragma once
#include <iostream>
#include <string>
#include <vector>

std::string parseStr(std::string text, std::vector<std::string> stop_words, int ngram_min_length, int ngram_max_length);
std::string deletePunct(std::string text);
std::string stringToLower(std::string text);
std::vector<std::string> splitWords(std::string text, std::vector<std::string> vector);
std::vector<std::string> deleteStopWords(std::vector<std::string> stop_words, std::vector<std::string> vector);
std::string generateNgrams(std::vector<std::string> vector, int min_ngram_length, int max_ngram_length);