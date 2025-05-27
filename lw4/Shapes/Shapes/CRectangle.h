#pragma once
#include "CBaseShape.h"
#include "CPoint.h"

class CRectangle final : public CBaseShape
{
public:
	CRectangle(CPoint lefTop, CPoint rightBottom, uint32_t fillColor, uint32_t outlineColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

	~CRectangle() = default;

private:
	CPoint m_leftTop, m_rightBottom;
};