#define _USE_MATH_DEFINES
#include "CCircle.h"
#include <iostream>
#include <math.h>

CCircle::CCircle(CPoint center, double radius, uint32_t fillColor, uint32_t outlineColor)
	: CBaseShape(fillColor, outlineColor)
	, m_center(center)
	, m_radius(radius)
{
}

double CCircle::GetArea() const
{
	return M_PI * m_radius * m_radius ;
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

std::string CCircle::ToString() const
{
	return "Circle\nCircle centre: " + m_center.ToString()
		+ "Circle radius: " + std::to_string(m_radius) + "\n"
		+ "Circle area: " + std::to_string(GetArea()) + "\n"
		+ "Circle perimeter: " + std::to_string(GetPerimeter()) + "\n"
		+ CBaseShape::ToString();
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}
