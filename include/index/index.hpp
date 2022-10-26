#pragma once
#include <string>
#include <vector>

struct term
{
	int doc_count;
	std::vector<int> pos;
	std::string text;
	std::vector<std::pair<std::string, int>> doc_id_and_pos_count;
};

class Index
{
	private:
		std::pair<std::string, std::string> docs;
		std::pair<std::string, std::vector<term>> entries;
	public:
		std::pair<std::string, std::string> getDocs();
		std::pair<std::string, std::vector<term>> getEntries();
};

class indexBuilder
{
	private:
		std::vector<Index> indexes;
	public:
		void add_document(std::string document_id, std::string text);
		void setIndexes(Index index);
		std::vector<Index> getIndexes();
		Index index(std::string doc_key, std::string doc_text, std::string entries_key, std::vector<term> entries_terms);
};