#include "CrossSet.h"

int main(int argc, char* argv[])
{
	try
	{
		int num = ParseArgs(argc, argv);
		std::set<int> set1 = CreateFirstSet(num);
		std::set<int> set2 = CreateSecondSet(num);
		std::set<int> crossingSet = CrossSet(set1, set2);
		PrintSet(std::cout, set1);
		PrintSet(std::cout, set2);
		PrintSet(std::cout, crossingSet);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return 1;
	}

	return 0;
}