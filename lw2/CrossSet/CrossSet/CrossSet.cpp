#include <algorithm>
#include <iterator>
#include <string>
#include "CrossSet.h"


void PrintHelp()
{
	std::cout << "Use: CrossSet.exe [options] <int number>\n"
		<< "Options:\n"
		<< "  -h  Show this help message\n"
		<< "If no arguments are provided, input number in console.\n";
}

int ParseArgs(int argc, char* argv[])
{
	int num = 0;
	if (argc == 1)
	{
		std::cin >> num;
	}
	if (argc == 2)
	{
		if (std::string(argv[1]) == "-h")
		{
			PrintHelp();
			return -1;
		}
		else
		{
			num = stoi(std::string(argv[1]));
		}
	}
	if (num <= 0)
	{
		throw std::runtime_error("ERROR");
	}
	return num;
}

int FindDigitSum(int num)
{
	int sum = 0;
	while (num != 0)
	{
		sum += num % 10;
		num /= 10;
	}
	return sum;
}

std::set<int> CreateFirstSet(int n)
{
	std::set<int> set;
	for (int i = 1; i <= n; i++)
	{
		if (i % FindDigitSum(i) == 0)
		{
			set.insert(i);
		}
	}
	return set;
}

std::set<int> CreateSecondSet(int n)
{
	std::set<int> set;
	for (int i = 1; i <= n; i++)
	{
		if (FindDigitSum(i) % 2 == 0) 
		{
			set.insert(i); 
		}
	}
	return set;
}

std::set<int> CrossSet(const std::set<int>& set1, const std::set<int>& set2) 
{
	std::set<int> crossingSet;
	std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), std::inserter(crossingSet, crossingSet.begin()));

	return crossingSet;
}

void PrintSet(std::ostream& output, std::set<int> set)
{
	for (const auto& n : set)
	{
		std::cout << n << " ";
	}
	std::cout << "\n";
}

