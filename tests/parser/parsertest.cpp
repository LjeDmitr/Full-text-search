#include <parser/parser.hpp>
#include <string>
#include <gtest/gtest.h>

using namespace std;

TEST(Parser, normal_parsing_string)
{
	parser parserTest;
	parserTest.parseStr("Dr. Jekyll and Mr. Hyde", 3, 6);
	string expect = "jek 0 jeky 0 jekyl 0 jekyll 0 hyd 1 hyde 1";
	ASSERT_EQ(expect, parserTest.getParsingStr());
}

TEST(Parser, no_stop_words)
{
	parser parserTest;
	parserTest.parseStr("Jekyll Hyde", 3, 6);
	string expect = "jek 0 jeky 0 jekyl 0 jekyll 0 hyd 1 hyde 1";
	ASSERT_EQ(expect, parserTest.getParsingStr());
}

TEST(Parser, empty_string)
{
	parser parserTest;
	parserTest.parseStr("", 3, 6);
	string expect = "";
	ASSERT_EQ(expect, parserTest.getParsingStr());
}

TEST(Parser, only_stop_words)
{
	parser parserTest;
	parserTest.parseStr("and t if", 3, 6);
	string expect = "";
	ASSERT_EQ(expect, parserTest.getParsingStr());
}

TEST(Parser, no_ngrams)
{
	parser parserTest;
	parserTest.parseStr("Dr. Jekyll and Mr. Hyde", 7, 8);
	string expect = "";
	ASSERT_EQ(expect, parserTest.getParsingStr());
}

TEST(Parser, too_many_spaces_between_words)
{
	parser parserTest;
	parserTest.parseStr("    Dr.    Jekyll     and     Mr.     Hyde    ", 3, 6);
	string expect = "jek 0 jeky 0 jekyl 0 jekyll 0 hyd 1 hyde 1";
	ASSERT_EQ(expect, parserTest.getParsingStr());
}

TEST(Parser, one_word)
{
	parser parserTest;
	parserTest.parseStr("Jekyll", 3, 6);
	string expect = "jek 0 jeky 0 jekyl 0 jekyll 0";
	ASSERT_EQ(expect, parserTest.getParsingStr());
}


TEST(Parser, no_punct)
{
	parser parserTest;
	parserTest.parseStr("Dr Jekyll and Mr Hyde", 3, 6);
	string expect = "jek 0 jeky 0 jekyl 0 jekyll 0 hyd 1 hyde 1";
	ASSERT_EQ(expect, parserTest.getParsingStr());
}

TEST(Parser, only_uppercase)
{
	parser parserTest;
	parserTest.parseStr("DR. JEKYLL AND MR. HYDE", 3, 6);
	string expect = "jek 0 jeky 0 jekyl 0 jekyll 0 hyd 1 hyde 1";
	ASSERT_EQ(expect, parserTest.getParsingStr());
}

TEST(Parser, no_uppercase)
{
	parser parserTest;
	parserTest.parseStr("dr. jekyll and mr. hyde", 3, 6);
	string expect = "jek 0 jeky 0 jekyl 0 jekyll 0 hyd 1 hyde 1";
	ASSERT_EQ(expect, parserTest.getParsingStr());
}

TEST(Parser, repeating_word)
{
	parser parserTest;
	parserTest.parseStr("The Matrix reload matrix", 3, 6);
	string expect = "mat 0 matr 0 matri 0 matrix 0 rel 1 relo 1 reloa 1 reload 1 mat 2 matr 2 matri 2 matrix 2";
	ASSERT_EQ(expect, parserTest.getParsingStr());
}