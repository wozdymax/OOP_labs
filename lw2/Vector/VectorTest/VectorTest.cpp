#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <sstream>
#include <string>
#include "../Vector/Vector.h"

TEST_CASE("Test vector read")
{
	std::vector<double> numbers;
	std::string line = "1.0 2 3.659512";
	std::istringstream input(line);
	CHECK_NOTHROW(numbers = ReadNumbers(input));

	std::vector<double> expectedResult = { 1.0, 2, 3.659512 };
	CHECK(numbers == expectedResult);

	line = "1 2 3 a";
	std::istringstream incorrectInput(line);
	CHECK_THROWS(ReadNumbers(incorrectInput));

	line = "";
	std::istringstream emptyInput(line);
	CHECK_NOTHROW(numbers = ReadNumbers(emptyInput));
	expectedResult = {};
	CHECK(numbers == expectedResult);
}

TEST_CASE("Test vector processing")
{
	std::vector<double> numbers = {1.0, 2.0, 3.0, 4.0};
	std::vector<double> processedNumbers;
	CHECK_NOTHROW(processedNumbers = ProcessNumbers(numbers));

	std::vector<double> expectedResult = { 0.5, 1, 1.5, 2 };
	CHECK(processedNumbers == expectedResult);

	numbers = { -4.9, 0, -5.6, -3, -1.1111 };
	CHECK_THROWS(processedNumbers = ProcessNumbers(numbers));

	numbers = { -1.0, -2.0, -3.0, -4.0 };
	CHECK_NOTHROW(processedNumbers = ProcessNumbers(numbers));

	expectedResult = { 2, 4, 6, 8 };
	CHECK(processedNumbers == expectedResult);
	
	numbers = {};
	CHECK_NOTHROW(processedNumbers = ProcessNumbers(numbers));

	expectedResult = {};
	CHECK(processedNumbers == expectedResult);
}

TEST_CASE("Test vector sort output")
{
	std::vector<double> numbers = { 5.45, 12.3457, 3.98932, 5.902, 4.1456 };
	std::string expectedResult = "3.989 4.146 5.450 5.902 12.346\n";
	std::ostringstream output;
	PrintSortedNumbers(output, numbers);
	CHECK(output.str() == expectedResult);

	numbers = {};
	expectedResult = "\n";
	output.str("");
	PrintSortedNumbers(output, numbers); 
	CHECK(output.str() == expectedResult); 
}