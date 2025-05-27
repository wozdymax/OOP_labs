#include "CRectangle.h"
#include <iostream>

CRectangle::CRectangle(CPoint lefTop, CPoint rightBottom, uint32_t fillColor, uint32_t outlineColor)
	: CBaseShape(fillColor, outlineColor)
	, m_leftTop(lefTop)
	, m_rightBottom(rightBottom)
{
}

double CRectangle::GetWidth() const
{
	return m_rightBottom.x - m_leftTop.x;
}

double CRectangle::GetHeight() const
{
	return m_leftTop.y - m_rightBottom.y;
}

double CRectangle::GetArea() const
{
	return GetWidth() * GetHeight() ;
}

double CRectangle::GetPerimeter() const
{
	return 2 * (GetWidth() + GetHeight());
}

std::string CRectangle::ToString() const
{
	return "Rectangle\nLeft top vertex: " + m_leftTop.ToString()
		+ "Left bottom vertex: " + CPoint({m_leftTop.x, m_rightBottom.y}).ToString()
		+ "Right bottom vertex: " + m_rightBottom.ToString()
		+ "Right top vertex: " + CPoint({ m_rightBottom.x, m_leftTop.y }).ToString()
		+ "Rectangle width: " + std::to_string(GetWidth()) + "\n"
		+ "Rectangle height: " + std::to_string(GetHeight()) + "\n"
		+ "Rectangle area: " + std::to_string(GetArea()) + "\n"
		+ "Rectangle perimeter: " + std::to_string(GetPerimeter()) + "\n"
		+ CBaseShape::ToString();
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
	return m_rightBottom;
}


