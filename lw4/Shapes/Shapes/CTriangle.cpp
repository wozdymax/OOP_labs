#include "CTriangle.h"
#include  "UtilityFunctions.h"
#include <iostream>

CTriangle::CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t fillColor, uint32_t outlineColor)
	: CBaseShape(fillColor, outlineColor)
	, m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
}

double CTriangle::GetArea() const
{
	return 0.5 * abs(GetDeterminant(m_vertex1, m_vertex2, m_vertex3));
}

double CTriangle::GetPerimeter() const
{
	return m_vertex1.GetDistanseTo(m_vertex2) + m_vertex2.GetDistanseTo(m_vertex3) + m_vertex3.GetDistanseTo(m_vertex1);
}

std::string CTriangle::ToString() const
{
	return "Triangle\nVertex 1: " + m_vertex1.ToString() 
		+ "Vertex 2: " + m_vertex2.ToString() 
		+ "Vertex 3: " + m_vertex3.ToString() 
		+ "Triangle area: " + std::to_string(GetArea()) + "\n"
		+ "Triangle perimeter: " + std::to_string(GetPerimeter()) + "\n"
		+ CBaseShape::ToString();
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}
