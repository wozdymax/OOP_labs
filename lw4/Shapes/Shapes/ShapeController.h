#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <map>
#include "IShape.h"

class ShapeController
{
public:
	ShapeController(std::istream& input, std::ostream& output);

	void HandleUserInput(const std::string& line);
	void PrintTwoShapes();

private:
	std::istream& m_input;
	std::ostream& m_output;

	std::vector<std::unique_ptr<IShape>> m_shapes;

	using Handler = std::function<void()>;
	using ActionMap = std::map<std::string, Handler>;
	const ActionMap m_actionMap;

	void AddCircle();
	void AddRectangle();
	void AddTriangle();
	void AddLine();

	IShape* GetShapeWithMaxArea() const;
	IShape* GetShapeWithMinPerimeter() const;

	uint32_t ColorToInt(const std::string& line);
};