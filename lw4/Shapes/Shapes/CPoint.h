#pragma once
#include <cmath>
#include <string>

struct CPoint 
{
	double x;
	double y;

	double GetDistanseTo(const CPoint& other) const
	{
		return std::hypot(x - other.x, y - other.y);
	}

	std::string ToString() const
	{
		return "(" + std::to_string(x) + ", " + std::to_string(y) + ")\n";
	}
};
