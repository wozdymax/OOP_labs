#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include "CPoint.h"

inline std::string IntColorToHexString(uint32_t color)
{
    std::stringstream hex;
    hex << std::setfill('0') << std::setw(6) << std::hex << color;
    return hex.str();
}

inline double GetDeterminant(CPoint v1, CPoint v2, CPoint v3)
{
    return (v1.x - v3.x) * (v2.y - v3.y) - (v2.x - v3.x) * (v1.y - v3.y);
}