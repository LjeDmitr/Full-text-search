#include <parser/parser.hpp>
#include <string>
#include <gtest/gtest.h>

using namespace std;

TEST(parser, normalParsingString)
{
	string stop_words[] = {"and", "dr", "mr"};
	string result = parseStr("Dr. Jekyll and Mr. Hyde", stop_words, 3, 6);
	string expect = "jek 0 jeky 0 jekyl 0 jekyll 0 hyd 1 hyde 1";
	ASSERT_EQ(expect, result);
}

TEST(deletePuncts, correctData)
{
	string result = deletePunct("Hello, World.");
	string expect = "Hello World";
	ASSERT_EQ(expect, result);
}

TEST(deletePuncts, noPunctString)
{
	string result = deletePunct("Hello World");
	string expect = "Hello World";
	ASSERT_EQ(expect, result);
}

TEST(deletePuncts, checkViodString)
{
	string result = deletePunct("");
	string expect = "";
	ASSERT_EQ(expect, result);
}

TEST(stringToLow, correctData)
{
	string result = stringToLower("Hello World");
	string expect = "hello world";
	ASSERT_EQ(expect, result);
}

TEST(stringToLow, noLowerCase)
{
	string result = stringToLower("hello world");
	string expect = "hello world";
	ASSERT_EQ(expect, result);
}

TEST(stringToLow, checkViodString)
{
	string result = stringToLower("");
	string expect = "";
	ASSERT_EQ(expect, result);
}