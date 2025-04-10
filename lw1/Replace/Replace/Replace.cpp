#include <iostream>
#include <optional>
#include <string>
#include <fstream>
#include <algorithm>

struct Args
{
	std::string inputFile;
	std::string outputFile;
	std::string findingWord;
	std::string replacingWord;
	bool isStdIn = false;
};

void PrintHelp()
{
	std::cout << "Use: Replace.exe [options] <input file> <output file> <search string> <replace string>\n"
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
		std::cin >> result.findingWord;
		std::cin >> result.replacingWord;
		return result;
	}
	if ((argc == 2) && (std::string(argv[1]) == "-h"))
	{
		PrintHelp();
		return std::nullopt;
	}
	if (argc != 5)
	{
		return std::nullopt;
	}

	result.inputFile = argv[1];
	result.outputFile = argv[2];
	result.findingWord = argv[3];
	result.replacingWord = argv[4];

	return result;
}

std::string ReplaceString(const std::string& text, const std::string& findingWord, const std::string& replaceWord)
{
	size_t pos = 0;
	std::string newText;
	while (pos < text.length())
	{
		size_t newPos = text.find(findingWord, pos);
		newText.append(text, pos, newPos - pos);
		if (newPos < text.length())
		{
			newText.append(replaceWord);
			pos = newPos + findingWord.length();
		}
		else
		{
			pos = newPos;
		}
	}
	return newText;
}

void Replace(const Args& args)
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

	std::string line;
	while (std::getline(input, line))
	{
		output << ReplaceString(line, args.findingWord, args.replacingWord) << std::endl;
	}
}

int main(int argc, char* argv[])
{
	std::optional<Args> args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	Replace(*args);

	return 0;
}