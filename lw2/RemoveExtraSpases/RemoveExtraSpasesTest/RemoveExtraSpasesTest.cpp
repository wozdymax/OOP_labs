#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "..\RemoveExtraSpases\RemoveExtraBlanks.h"

TEST_CASE("Test remove extra spaces")
{
	std::string line = " 1          2 3      4      5";
	std::string newLine = RemoveExtraSpaces(line);
	CHECK(newLine == "1 2 3 4 5");

	line = "     1          ";
	newLine = RemoveExtraSpaces(line);
	CHECK(newLine == "1");

	line = "                ";
	newLine = RemoveExtraSpaces(line);
	CHECK(newLine == "");

	line = "";
	newLine = RemoveExtraSpaces(line);
	CHECK(newLine == "");
}