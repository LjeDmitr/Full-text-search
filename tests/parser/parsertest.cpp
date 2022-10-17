#include <parser/parser.hpp>
#include <string>
#include <gtest/gtest.h>

using namespace std;

TEST(parser, normal_parsing_string)
{
	string result = parseStr("Dr. Jekyll and Mr. Hyde", 3, 6);
	string expect = "jek 0 jeky 0 jekyl 0 jekyll 0 hyd 1 hyde 1";
	ASSERT_EQ(expect, result);
}

TEST(parser, no_stop_words)
{
	string result = parseStr("Jekyll Hyde", 3, 6);
	string expect = "jek 0 jeky 0 jekyl 0 jekyll 0 hyd 1 hyde 1";
	ASSERT_EQ(expect, result);
}

TEST(parser, empty_string)
{
	string result = parseStr("", 3, 6);
	string expect = "";
	ASSERT_EQ(expect, result);
}

TEST(parser, only_stop_words)
{
	string result = parseStr("and t if", 3, 6);
	string expect = "";
	ASSERT_EQ(expect, result);
}

TEST(parser, no_ngrams)
{
	string result = parseStr("Dr. Jekyll and Mr. Hyde", 7, 8);
	string expect = "";
	ASSERT_EQ(expect, result);
}

TEST(parser, too_many_spaces_between_words)
{
	string result = parseStr("    Dr.    Jekyll     and     Mr.     Hyde    ", 3, 6);
	string expect = "jek 0 jeky 0 jekyl 0 jekyll 0 hyd 1 hyde 1";
	ASSERT_EQ(expect, result);
}

TEST(parser, one_word)
{
	string result = parseStr("Jekyll", 3, 6);
	string expect = "jek 0 jeky 0 jekyl 0 jekyll 0";
	ASSERT_EQ(expect, result);
}


TEST(parser, no_punct)
{
	string result = parseStr("Dr Jekyll and Mr Hyde", 3, 6);
	string expect = "jek 0 jeky 0 jekyl 0 jekyll 0 hyd 1 hyde 1";
	ASSERT_EQ(expect, result);
}

TEST(parser, only_uppercase)
{
	string result = parseStr("DR. JEKYLL AND MR. HYDE", 3, 6);
	string expect = "jek 0 jeky 0 jekyl 0 jekyll 0 hyd 1 hyde 1";
	ASSERT_EQ(expect, result);
}

TEST(parser, no_uppercase)
{
	string result = parseStr("dr. jekyll and mr. hyde", 3, 6);
	string expect = "jek 0 jeky 0 jekyl 0 jekyll 0 hyd 1 hyde 1";
	ASSERT_EQ(expect, result);
}