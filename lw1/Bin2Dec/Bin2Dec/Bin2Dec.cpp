#include <iostream>
#include <optional>
#include <string>
#include <fstream>
#include <algorithm>
#include <cmath>

const std::string ERROR = "ERROR";

void PrintHelp()
{
	std::cout << "Use: Bin2Dec.exe [options] <input file> <output file>\n"
		<< "Options:\n"
		<< "  -h  Show this help message\n"
		<< "If no arguments are provided, input is read from stdin and output is printed to console.\n";
}
 
std::string ParseArgs(int argc, char* argv[])
{
	std::string strNum;
	if (argc == 1)
	{
		std::cin >> strNum;
	}
	if (argc == 2)
	{
		strNum = std::string(argv[1]); 
		if (std::string(argv[1]) == "-h")
		{
			PrintHelp();
		}
	}
	if (argc > 2)
	{
		throw std::runtime_error(ERROR);
	}

	return strNum;
}

bool IsBinNumber(const std::string& strBinNumber)
{
	for (char ch : strBinNumber)
	{
		if (ch != '0' && ch != '1')
		{
			return false;
		}
	}
	return true;
}

void ConvertBinToDec(const std::string& strBinNumber)
{
	if (!IsBinNumber(strBinNumber))
	{
		throw std::runtime_error(ERROR);
	}

	int number = 0;
	int binLength = strBinNumber.length();
	if (binLength >= 32)
	{
		throw std::runtime_error(ERROR);
	}

	for (char bit : strBinNumber)
	{
		number = (number << 1) | (bit - '0');
	}

	std::cout << number;
}

int main(int argc, char* argv[])
{
	try
	{
		std::string binNum = ParseArgs(argc, argv);
		if (binNum != "-h")
		{
			ConvertBinToDec(binNum);
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return 1;
	}

	return 0;
}