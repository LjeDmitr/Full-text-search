#include <parser/parser.hpp>
#include <string>
#include <gtest/gtest.h>

using namespace std;

TEST(parser, normalParsingString)
{
	vector<string> stop_words = {"and", "dr", "mr"};
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

TEST(delete_stop_words, correctData)
{
	vector<string> words;
	words.push_back("hello");
	words.push_back("a");
	words.push_back("world");
	words.push_back("b");
	words.push_back("c");
	vector<string> stop_words = {"a", "b", "c"};
	words = deleteStopWords(stop_words, words);
	vector<string> expect;
	expect.push_back("hello");
	expect.push_back("world");
	ASSERT_EQ(expect, words);
}

TEST(delete_stop_words, noStopWords)
{
	vector<string> words;
	words.push_back("hello");
	words.push_back("world");
	vector<string> stop_words = {"a", "b", "c"};
	words = deleteStopWords(stop_words, words);
	vector<string> expect;
	expect.push_back("hello");
	expect.push_back("world");
	ASSERT_EQ(expect, words);
}

TEST(delete_stop_words, onlyStopWords)
{
	vector<string> words;
	words.push_back("a");
	words.push_back("b");
	words.push_back("c");
	vector<string> stop_words = {"a", "b", "c"};
	words = deleteStopWords(stop_words, words);
	vector<string> expect;
	ASSERT_EQ(expect, words);
}

TEST(delete_stop_words, noWords)
{
	vector<string> words;
	vector<string> stop_words = {"a", "b", "c"};
	words = deleteStopWords(stop_words, words);
	vector<string> expect;
	ASSERT_EQ(expect, words);
}

TEST(generate_ngramm, correctData)
{
	vector<string> words;
	words.push_back("hello");
	words.push_back("world");
	string result = generateNgrams(words, 3, 5);
	string expect = "hel 0 hell 0 hello 0 wor 1 worl 1 world 1";
	ASSERT_EQ(expect, result);
}

TEST(generate_ngramm, noGenerateNgramm)
{
	vector<string> words;
	words.push_back("hello");
	words.push_back("world");
	string result = generateNgrams(words, 6, 7);
	string expect = "";
	ASSERT_EQ(expect, result);
}

TEST(generate_ngramm, noWords)
{
	vector<string> words;
	string result = generateNgrams(words, 0, 7);
	string expect = "";
	ASSERT_EQ(expect, result);
}