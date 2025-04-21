#include <iostream>
#include <optional>
#include <string>
#include <fstream>
#include <algorithm>
#include <cmath>

struct Args
{
	std::string inputFile;
	std::string outputFile;
	bool isStdIn = false;
};

void PrintHelp()
{
	std::cout << "Use: Bin2Dec.exe [options] <input file> <output file>\n"
		<< "Options:\n"
		<< "  -h  Show this help message\n"
		<< "If no arguments are provided, input is read from stdin and output is printed to console.\n";
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	Args result;
	if (argc == 1)
	{
		result.isStdIn = true;
		return result;
	}
	if ((argc == 2) && (std::string(argv[1]) == "-h"))
	{
		PrintHelp();
		return std::nullopt;
	}
	if (argc != 3)
	{
		return std::nullopt;
	}

	result.inputFile = argv[1];
	result.outputFile = argv[2];

	return result;
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

std::optional<int> ConvertBinToDec(const std::string& strBinNumber)
{
	if (!IsBinNumber(strBinNumber))
	{
		return std::nullopt; 
	}

	int number = 0;
	int binLength = strBinNumber.length();
	if (binLength >= 32)
	{
		return std::nullopt;
	}

	for (int i = 0; i < binLength; i++)
	{
		number += (strBinNumber[i] - '0') * std::pow(2, binLength - i - 1);
	}

	return number;
}

void Convert(const Args& args)
{
	std::ifstream inputFile;
	std::ofstream outputFile;
	std::istream& input = (args.isStdIn ? std::cin : inputFile);
	std::ostream& output = (args.isStdIn ? std::cout : outputFile);
	
	if (!args.isStdIn)
	{
		inputFile.open(args.inputFile);
		if (!inputFile.is_open())
		{
			std::cerr << "Can`t open input file!";
			return;
		}
		outputFile.open(args.outputFile);
		if (!outputFile.is_open())
		{
			std::cerr << "Can`t open output file!";
			return;
		}
	}

	std::string binNumber;
	input >> binNumber;

	std::optional<int> number = ConvertBinToDec(binNumber);
	if(!number)
	{
		output << "ERROR";
		return;
	}
	output << *number;
}

int main(int argc, char* argv[])
{
	std::optional<Args> args = ParseArgs(argc, argv);
	if (!args)
	{
		std::cout << "ERROR";
		return 1;
	}

	Convert(*args);

	return 0;
}