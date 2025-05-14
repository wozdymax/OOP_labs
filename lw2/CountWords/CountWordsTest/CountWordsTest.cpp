#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <sstream>
#include "../CountWords/CountWords.h"

TEST_CASE("Test map read")
{
	CountedWordsList wordList;
	std::string line = "cat cat dog\n cat cow";
	std::istringstream input1(line);
	wordList = ReadWords(input1);
	CountedWordsList result1
	{
		{"cat", 3}, {"cow", 1}, {"dog", 1}
	};
	CHECK(wordList == result1);

	line = "";
	std::istringstream input2(line); 
	wordList = ReadWords(input2); 
	CountedWordsList result2{};
	CHECK(wordList == result2);
}

TEST_CASE("Test map ouptut")
{
	CountedWordsList wordList{};
	std::ostringstream output;
	PrintStatistics(wordList, output);
	std::string result = "";
	CHECK(output.str() == result);

	wordList = { 
		{"house", 3}, {"school", 5}, {"village", 6}
	};
	PrintStatistics(wordList, output); 
	result = "house->3\nschool->5\nvillage->6\n";
	CHECK(output.str() == result); 
}