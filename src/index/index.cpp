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

static bool hashUniquenessCheck(string hash, vector<Index> indexes) {
	for (auto element : indexes) {
		if (hash == element.getEntries().first) {
			return false;
		}
	}
	return true;
}

static term createTerm(pair<string, int> ngram, string doc_id) {
	term term_obj;
	term_obj.text = ngram.first;
	term_obj.doc_count = 1;
	term_obj.doc_id_and_pos_count.push_back(make_pair(doc_id, 1));
	term_obj.pos.push_back(ngram.second);
	return term_obj;
}

static bool checkDocId(string doc_id, vector<pair<string, int>> doc_id_and_pos_count) {
	for (auto docs_id : doc_id_and_pos_count) {
		if (doc_id == docs_id.first) {
			return false;
		}
	}
	return true;
}

void Index::correct_index(string doc_id, string hash, pair<string, int> ngram) {
	if (doc_id == docs.first) {
		for (size_t i = 0; i < entries.second.size(); i++) {
			for (size_t j = 0; j < entries.second[i].doc_id_and_pos_count.size(); j++) {
				if (doc_id == entries.second[i].doc_id_and_pos_count[j].first) {
					entries.second[i].doc_id_and_pos_count[j].second++;
					entries.second[i].pos.push_back(ngram.second);
				}
			}
		}
	} else if (hash == entries.first && checkDocId(doc_id, doc_id_and_pos_count)) {
		for (size_t i = 0; i < entries.second.size(); i++) {
			entries.second[i].doc_id_and_pos_count.push_back(make_pair(doc_id, 1));
			entries.second[i].doc_count++;
		}
	}
}

void indexBuilder::add_document(string document_id, string text) {
	parser parsing_string;
	parsing_string.parseStr(text, 3, 6);
	string hash_hex_str;
	int cur_term_pos = -1;
    vector<term> entries_terms;
	vector<pair<string, int>> ngrams = parsing_string.getNgrams();
	for (size_t i = 0; i < ngrams.size(); i++) {
		if (cur_term_pos != ngrams[i].second) {
			picosha2::hash256_hex_string(ngrams[i].first, hash_hex_str);
			hash_hex_str = hash_hex_str.substr(0, 6);
			if (hashUniquenessCheck(hash_hex_str, indexes)) {
				cur_term_pos = ngrams[i].second;
				while (cur_term_pos == ngrams[i].second && i < ngrams.size()) {
					entries_terms.push_back(createTerm(ngrams[i], document_id));
					i++;
				}
				i--;
				indexes.push_back(index(document_id, text, hash_hex_str, entries_terms));
			} else {
				for (size_t j = 0; j < indexes.size(); j++) {
					indexes[j].correct_index(document_id, hash_hex_str, ngrams[i]);
				}
				cur_term_pos = ngrams[i].second;
			}
		}
	}
}