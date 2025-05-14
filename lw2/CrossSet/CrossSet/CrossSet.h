#pragma once
#include <iostream>
#include <set>

int ParseArgs(int argc, char* argv[]);

std::set<int> CreateFirstSet(int n);

std::set<int> CreateSecondSet(int n);

std::set<int> CrossSet(const std::set<int>& set1, const std::set<int>& set2);

void PrintSet(std::ostream& output, std::set<int> set);
