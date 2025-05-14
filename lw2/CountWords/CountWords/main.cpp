#include "CountWords.h"

int main()
{ 
	CountedWordsList wordList;

	wordList = ReadWords(std::cin);
	PrintStatistics(wordList, std::cout);

	return 0;
}