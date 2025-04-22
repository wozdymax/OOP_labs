#include "Vector.h"
#include <iomanip>
#include <algorithm>

std::vector<double> ReadNumbers(std::istream& input)
{
	double num;
	std::vector<double> numbers;
	while (input >> num)
	{
		numbers.push_back(num);
	}

	if (input.fail() && !input.eof())
	{
		throw std::runtime_error("ERROR");
	}

	return numbers;
}

std::vector<double> ProcessNumbers(const std::vector<double> numbers)
{
	std::vector<double> processedNumbers = {};
	if (numbers.empty())
	{
		return processedNumbers;
	}
	double maxNum = *std::max_element(begin(numbers), end(numbers));
	if (maxNum == 0)
	{
		throw std::runtime_error("It is impossible to divide by 0");
	}

	for (auto num : numbers)
	{
		processedNumbers.push_back(num / (maxNum / 2));
	}

	return processedNumbers;
}

void PrintSortedNumbers(std::ostream& output, std::vector<double>& numbers)
{
	size_t size = numbers.size();
	std::sort(begin(numbers), end(numbers));
	output << std::fixed << std::setprecision(3);
	for (int i = 0; i < size; i++)
	{
		output << numbers[i];
		if (i != size - 1)
		{
			output << " ";
		}
	}
	output << "\n";
}

