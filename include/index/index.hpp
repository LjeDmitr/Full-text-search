#pragma once
#include <string>
#include <vector>

class Index
{
	private:
		std::pair<std::string, std::string> docs;
		std::pair<std::string, std::vector<term>> entries;
	public:
		std::pair<std::string, std::string> getDocs();
		std::pair<std::string, std::vector<term>> getEntries();
};