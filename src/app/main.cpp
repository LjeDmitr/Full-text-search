#include <index/index.hpp>
#include <iostream>

using namespace std;

int main() {
	indexBuilder test;
	test.add_document("199903", "The Matrix");
	test.add_document("200305", "The Matrix Reloaded");
	test.add_document("200311", "The Matrix Revolutions");
	for (auto index : test.getIndexes()) {
		textIndexWriter::write("index", index);
	}
	return 0;
}