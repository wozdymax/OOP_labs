#include <iostream>
#include "ShapeController.h"

int main()
{
	ShapeController UI(std::cin, std::cout);
	std::string line;
	while (std::getline(std::cin, line))
	{
		try
		{
			UI.HandleUserInput(line);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what();
		}
	}
	UI.PrintTwoShapes();

	return 0;

}
