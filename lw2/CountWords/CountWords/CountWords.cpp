#include "CountWords.h"

CountedWordsList ReadWords(std::istream& input)
{
	std::string word;
	CountedWordsList wordList;
	while (input >> word)
	{
		if (wordList.count(word))
		{
			wordList[word]++;
		}
		else
		{
			wordList[word] = 1;
		}
	}

	return wordList;
}

void PrintStatistics(CountedWordsList wordList, std::ostream& output)
{
	for (const auto& [word, quantity] : wordList)
	{
		output << word << "->" << quantity << std::endl;
	}
}