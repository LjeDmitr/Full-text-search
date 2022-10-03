#pragma once
#include <iostream>
#include <string>

std::string parseStr(std::string text, std::string stop_words[], int ngram_min_length, int ngram_max_length);