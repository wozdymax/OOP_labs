#include <iostream>
#include <sstream>
#include "RemoveExtraBlanks.h"

std::string RemoveExtraSpaces(const std::string& arg)
{
	std::istringstream line(arg);
	std::string word, newLine;

	while (line >> word)
	{
		if (!newLine.empty())
		{
			newLine += " ";
		}
		newLine += word;
	}
	
	return newLine;
}


