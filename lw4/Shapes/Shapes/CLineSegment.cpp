#include "CLineSegment.h"
#include "UtilityFunctions.h"
#include <algorithm>


CLineSegment::CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t color)
    : m_StartPoint(startPoint)
    , m_EndPoint(endPoint)
    , m_color(color)
{
}

double CLineSegment::GetArea() const
{
    return 0.0;
}

double CLineSegment::GetPerimeter() const
{
    return m_StartPoint.GetDistanseTo(m_EndPoint);
}

std::string CLineSegment::ToString() const
{
    return  "Line segment\nShape area: " + std::to_string(GetArea()) + "\n"
        + "Shape perimeter: " + std::to_string(GetPerimeter()) + "\n"
        + "Outline color: " + IntColorToHexString(m_color) + "\n";
}

uint32_t CLineSegment::GetOutlineColor() const
{
    return m_color;
}

CPoint CLineSegment::GetStartPoint() const
{
    return m_StartPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
    return m_EndPoint;
}
