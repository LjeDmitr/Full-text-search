#include <index/index.hpp>
#include <parser/parser.hpp>
#include <fstream>
#include <picosha2.h>

using namespace std;

void Index::setDocs (string key, string text) {
	docs = make_pair(key, text);
}

pair<string, string> Index::getDocs() {
	return docs;
}

void Index::setEntries (string key, vector<term> terms) {
	entries = make_pair(key, terms);
}

pair<string, vector<term>> Index::getEntries() {
	return entries;
}

void indexBuilder::setIndexes(Index index) {
	indexes.push_back(index);
}

vector<Index> indexBuilder::getIndexes() {
	return indexes;
}
