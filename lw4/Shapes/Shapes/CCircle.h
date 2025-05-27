#pragma once
#include "CBaseShape.h"
#include "CPoint.h"

class CCircle final : public CBaseShape
{
public:
	CCircle(CPoint center, double radius, uint32_t fillColor, uint32_t outlineColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

	CPoint GetCenter() const;
	double GetRadius() const;

	~CCircle() = default;

private:
	CPoint m_center;
	double m_radius;
};