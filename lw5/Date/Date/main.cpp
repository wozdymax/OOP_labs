#include <iostream>
#include "CDate.h"

int main()
{
	CDate date1(29, Month::FEBRUARY, 2004);
	date1.GetMonth();
	date1.GetDay();
	return 0;
}
