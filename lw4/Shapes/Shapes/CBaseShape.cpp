#include "CBaseShape.h"
#include "UtilityFunctions.h"

CBaseShape::CBaseShape(uint32_t fillColor, uint32_t outlineColor)
	: m_fillColor(fillColor)
	, m_outlineColor(outlineColor)
{
}

std::string CBaseShape::ToString() const
{
	return "Outline color: " + IntColorToHexString(m_outlineColor) + "\n"
		+ "Fill color: " + IntColorToHexString(m_fillColor) + "\n";
}

uint32_t CBaseShape::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CBaseShape::GetFillColor() const
{
	return m_fillColor;
}
