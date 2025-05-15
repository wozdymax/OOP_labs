#include "Vector.h"
#include <iomanip>
#include <algorithm>

const std::string ZERO_DIVIDE_ERROR = "It is impossible to divide by 0";
const std::string ERROR = "ERROR";


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
		throw std::runtime_error(ERROR);
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
		throw std::runtime_error(ZERO_DIVIDE_ERROR);
	}

	auto splitInHalf = [&processedNumbers, maxNum](const double& n) {processedNumbers.push_back(n / (maxNum / 2));};
	std::for_each(numbers.begin(), numbers.end(), splitInHalf); 

	return processedNumbers;
}

void PrintSortedNumbers(std::ostream& output, std::vector<double>& numbers)
{
	size_t size = numbers.size();
	std::sort(begin(numbers), end(numbers));
	output << std::fixed << std::setprecision(3);

	auto print = [&output](const double& n) {output << n << " ";};
	std::for_each(numbers.begin(), numbers.end(), print); 
	output << "\n";
}

