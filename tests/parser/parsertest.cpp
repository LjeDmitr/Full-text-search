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

TEST(delete_puncts, correctData)
{
	string result = deletePunct("Hello, World.");
	string expect = "Hello World";
	ASSERT_EQ(expect, result);
}

TEST(delete_puncts, noPunctString)
{
	string result = deletePunct("Hello World");
	string expect = "Hello World";
	ASSERT_EQ(expect, result);
}

TEST(delete_puncts, checkViodString)
{
	string result = deletePunct("");
	string expect = "";
	ASSERT_EQ(expect, result);
}

TEST(string_to_low, correctData)
{
	string result = stringToLower("Hello World");
	string expect = "hello world";
	ASSERT_EQ(expect, result);
}

TEST(string_to_low, noLowerCase)
{
	string result = stringToLower("hello world");
	string expect = "hello world";
	ASSERT_EQ(expect, result);
}

TEST(string_to_low, checkViodString)
{
	string result = stringToLower("");
	string expect = "";
	ASSERT_EQ(expect, result);
}

TEST(split_words, correctData)
{
	vector<string> words;
	words = splitWords("hello world", words);
	vector<string> expect;
	expect.push_back("hello");
	expect.push_back("world");
	ASSERT_EQ(expect, words);
}

TEST(split_words, oneWord)
{
	vector<string> words;
	words = splitWords("helloworld", words);
	vector<string> expect;
	expect.push_back("helloworld");
	ASSERT_EQ(expect, words);
}

TEST(split_words, checkWhiteSpace)
{
	vector<string> words;
	words = splitWords("hello    world", words);
	vector<string> expect;
	expect.push_back("hello");
	expect.push_back("world");
	ASSERT_EQ(expect, words);
}

TEST(split_words, checkWhiteSpaceInBegin)
{
	vector<string> words;
	words = splitWords("   hello world", words);
	vector<string> expect;
	expect.push_back("hello");
	expect.push_back("world");
	ASSERT_EQ(expect, words);
}

TEST(split_words, checkWhiteSpaceInEnd)
{
	vector<string> words;
	words = splitWords("hello world   ", words);
	vector<string> expect;
	expect.push_back("hello");
	expect.push_back("world");
	ASSERT_EQ(expect, words);
}