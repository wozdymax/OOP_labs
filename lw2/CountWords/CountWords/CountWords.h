#pragma once
#include <iostream>
#include <string>
#include <map>

using CountedWordsList = std::map<std::string, int>;

CountedWordsList ReadWords(std::istream& input);
void PrintStatistics(CountedWordsList wordList, std::ostream& output);