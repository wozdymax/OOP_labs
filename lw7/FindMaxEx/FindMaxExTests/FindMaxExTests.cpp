#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <iostream>
#include "../FindMaxEx/FindMaxEx.h"

struct Sportsman
{
	std::string name;
	int weight;
	int height;
};

const int MAX_WEIGHT = 93;
const int MAX_HEIGHT = 195;
const std::vector<Sportsman> sportsmans{
	{"Ivan", MAX_WEIGHT, 180},
	{"Petr", 86, 185},
	{"Daniil", 90, MAX_HEIGHT}
};

bool CompareWeight(const Sportsman& first, const Sportsman& second)
{
	return first.weight < second.weight;
}

bool CompareHeight(const Sportsman& first, const Sportsman& second)
{
	return first.height < second.height;
}

TEST_CASE("Test with vector of integer")
{
	std::vector<int> arr{};
	int maxValue = 0;
	CHECK_FALSE(FindMaxEx(arr, maxValue, std::less<int>()));
	arr.push_back(23);
	CHECK(FindMaxEx(arr, maxValue, std::less<int>()));
	CHECK(maxValue == 23);
	arr.push_back(45);
	arr.push_back(10);
	arr.push_back(19);
	CHECK(FindMaxEx(arr, maxValue, std::less<int>()));
	CHECK(maxValue == 45);
	std::cout << "Vector of integer testing was completed success!\n";
}

TEST_CASE("Test with vector of sportsmans")
{
	Sportsman maxWeightSportsman;
	CHECK(FindMaxEx(sportsmans, maxWeightSportsman, CompareWeight));
	CHECK(maxWeightSportsman.weight == MAX_WEIGHT);

	Sportsman maxHeightSportsman;
	CHECK(FindMaxEx(sportsmans, maxHeightSportsman, CompareHeight));
	CHECK(maxHeightSportsman.height == MAX_HEIGHT);

	std::cout << "Vector of sportsmans testing was completed success!\n";
}