#include <string>
#include <cctype> 

using namespace std;

string deletePunct(string text) {
	for (int i = 0; i < (int)text.size() - 1; ++i) {
		if (ispunct(text[i])) {
			text.erase(i, 1);
		} 
	}
	return text;
}

string stringToLower(string text) {
	for (int i = 0; i < (int)text.size() - 1; ++i) {
		text[i] = (char)tolower(text[i]);
	}
	return text;
}