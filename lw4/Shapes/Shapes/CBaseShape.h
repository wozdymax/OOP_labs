#pragma once
#include "ISolidShape.h"

class CBaseShape : public ISolidShape
{
public:
	 CBaseShape(uint32_t fillColor, uint32_t outlineColor);

	 std::string ToString() const override;
	 uint32_t GetOutlineColor() const override;
	 uint32_t GetFillColor() const override;

	 ~CBaseShape() = default;
protected:
	uint32_t m_fillColor; 
	uint32_t m_outlineColor;
};