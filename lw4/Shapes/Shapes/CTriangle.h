#pragma once
#include "CBaseShape.h"
#include "CPoint.h"

class CTriangle final : public CBaseShape
{
public:
	CTriangle(CPoint vertex1, CPoint vertex2,CPoint vertex3, uint32_t fillColor,uint32_t outlineColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

	~CTriangle() = default;

private:
	CPoint m_vertex1, m_vertex2, m_vertex3;
};