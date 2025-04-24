#include <iostream>
#include "RemoveExtraBlanks.h"

int main()
{
	std::string line, newLine;
	while (std::getline(std::cin, line))
	{
		newLine = RemoveExtraSpaces(line);
		std::cout << newLine << "\n";
	}

	return 0;
}