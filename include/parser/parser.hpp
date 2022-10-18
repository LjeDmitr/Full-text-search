#pragma once
#include <iostream>
#include <string>
#include <vector>

class parser
{
	private:
		std::vector<std::pair<std::string, int>> ngrams;
		std::string parsing_str;
	public:
		void parseStr(std::string text, int ngram_min_length, int ngram_max_length);
		std::string getParsingStr();
		std::vector<std::pair<std::string, int>> getNgrams();
};