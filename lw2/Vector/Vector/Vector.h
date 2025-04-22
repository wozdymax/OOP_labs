#pragma once
#include <vector>
#include <iostream>

std::vector<double> ReadNumbers(std::istream& input);
std::vector<double> ProcessNumbers(const std::vector<double> numbers);
void PrintSortedNumbers(std::ostream& output, std::vector<double>& numbers);
