#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "../CrossSet/CrossSet.h"

TEST_CASE("Test first set creating")
{
	int n = 20;
	std::set<int> set = CreateFirstSet(n);
	std::set<int>resultSet = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 18, 20 }; 
	CHECK(set == resultSet);
}

TEST_CASE("Test second set creating")
{
	int n = 20;
	std::set<int> set = CreateSecondSet(n);
	std::set<int>resultSet = { 2, 4, 6, 8, 11, 13, 15, 17, 19, 20 };
	CHECK(set == resultSet);
}

TEST_CASE("Test sets crossing")
{
	int n = 20;
	std::set<int> set1 = CreateFirstSet(n); 
	std::set<int> set2 = CreateSecondSet(n);
	std::set<int> set = CrossSet(set1, set2);
	std::set<int>resultSet = { 2, 4, 6, 8, 20 };
	CHECK(set == resultSet);
}