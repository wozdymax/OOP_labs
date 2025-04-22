#include "Vector.h"

int main()
{
	try
	{
		std::vector<double> numbers = ReadNumbers(std::cin);
		std::vector<double> processedNumbers = ProcessNumbers(numbers);
		PrintSortedNumbers(std::cout, processedNumbers);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}

	return 0;
}