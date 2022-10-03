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