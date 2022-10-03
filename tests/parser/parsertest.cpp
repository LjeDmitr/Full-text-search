#include <parser/parser.hpp>
#include <string>
#include <gtest/gtest.h>

using namespace std;

TEST(parser, parsingString)
{
	string stop_words[] = {"and", "dr", "mr"};
	string result = parseStr("Dr. Jekyll and Mr. Hyde", stop_words, 3, 6);
	string expect = "jek 0 jeky 0 jekyl 0 jekyll 0 hyd 1 hyde 1";
	ASSERT_EQ(expect, result);
}