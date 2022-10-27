#pragma once
#include <iostream>
#include <string>
#include <vector>

class parser
{
	private:
		std::vector<std::pair<std::string, std::vector<int>>> ngrams;
		std::string parsing_str;
	public:
		void parseStr(std::string text, int ngram_min_length, int ngram_max_length);
		void createNewVector(int first_pos);
		std::string getParsingStr();
		std::vector<std::pair<std::string, std::vector<int>>> getNgrams();
};