#include "ShapeController.h"
#include "CCircle.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "UtilityFunctions.h"

#include <sstream>
#include <regex>

const std::string UNKNOW_COMMAND_ERROR = "Unknown command\n";
const std::string CIRCLE_INPUT_FORMAT = "\n<center pos (x y)> <radius> <fill color (RRGGBB)> <outline color (RRGGBB)>\n";
const std::string RECTANGLE_INPUT_FORMAT = "\n<left top pos (x y)> <right bottom pos (x y)> <fill color (RRGGBB)> <outline color (RRGGBB)>\n";
const std::string TRIANGLE_INPUT_FORMAT = "\n<3 vertces positions (x y)> <fill color> <outline color>\n";
const std::string LINE_SEGMENT_INPUT_FORMAT = "\n<start pos (x y)> <end pos (x y)> <color>\n";
const std::string INVALID_INPUT_FORMAT_ERROR = "Invalid input format";
const std::string INVALID_COLOR_FORMAT_ERROR = "Invalid color format";
const std::string INVALID_RADIUS_ERROR = "Radius should be greater than 0";
const std::string INVALID_RECT_COORDS_ERROR = "Left top vertex should be more left and top then right bottom";
const std::string INVALID_TRIANGLE_COORDS_ERROR = "Coordinates of degenerate triangle\n";
const std::string NO_SHAPES_MSG = "No shapes\n";
const std::string MAX_AREA_SHAPE_MSG = "Shape with max area: \n";
const std::string MIN_PERIMETER_SHAPE_MSG = "Shape with min perimeter: \n";
const std::string REG_HEX_COLOR = "^[0-9a-fA-F]{6}$";

ShapeController::ShapeController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({
		{ "circle", [this]() { AddCircle(); } },
		{ "line", [this]() { AddLine(); } },
		{ "triangle", [this]() { AddTriangle(); } },
		{ "rectangle", [this]() { AddRectangle(); } },
		{ "", [this]() {}}
		})
{
}

void ShapeController::HandleUserInput(const std::string& line)
{
	std::istringstream str(line);
	std::string command;

	str >> command;
	auto it = m_actionMap.find(command);
	if (it == m_actionMap.end())
	{
		throw std::runtime_error(UNKNOW_COMMAND_ERROR);
	}
	it->second();
}

bool IsValidColorFormat(const std::string& colorStr)
{
	static const std::regex colorRegex(REG_HEX_COLOR);
	return std::regex_match(colorStr, colorRegex);
}


uint32_t ShapeController::ColorToInt(const std::string& line)
{
	uint32_t num;
	std::stringstream ss;
	ss << std::hex << line;
	ss >> num;
	return num;
}

void ShapeController::AddCircle()
{
	m_output << CIRCLE_INPUT_FORMAT;
	double radius, x, y;
	std::string fillColorStr, outlineColorStr;

	if (!(m_input >> x >> y >> radius >> fillColorStr >> outlineColorStr))
	{
		throw std::invalid_argument(INVALID_INPUT_FORMAT_ERROR);
	}

	if (!IsValidColorFormat(fillColorStr) || !IsValidColorFormat(outlineColorStr))
	{
		throw std::invalid_argument(INVALID_COLOR_FORMAT_ERROR);
	}

	uint32_t fillColor = ColorToInt(fillColorStr);
	uint32_t outlineColor = ColorToInt(outlineColorStr);

	if (radius <= 0)
	{
		throw std::invalid_argument(INVALID_RADIUS_ERROR);
	}

	auto circle = std::make_unique<CCircle>(CPoint(x, y), radius, fillColor, outlineColor);
	m_shapes.push_back(std::move(circle));
}

void ShapeController::AddRectangle()
{
	m_output << RECTANGLE_INPUT_FORMAT;

	std::string fillColorStr, outlineColorStr;
	double lX, lY, rX, rY;

	if (!(m_input >> lX >> lY >> rX >> rY >> fillColorStr >> outlineColorStr))
	{
		throw std::invalid_argument(INVALID_INPUT_FORMAT_ERROR);
	}

	if (!IsValidColorFormat(fillColorStr) || !IsValidColorFormat(outlineColorStr))
	{
		throw std::invalid_argument(INVALID_COLOR_FORMAT_ERROR);
	}

	if (lX >= rX || lY <= rY)
	{
		throw std::invalid_argument(INVALID_RECT_COORDS_ERROR); 
	}

	uint32_t fillColor = ColorToInt(fillColorStr);
	uint32_t outlineColor = ColorToInt(outlineColorStr);

	auto rectangle = std::make_unique<CRectangle>(CPoint(lX, lY), CPoint(rX, rY), fillColor, outlineColor);
	m_shapes.push_back(std::move(rectangle));
}

void ShapeController::AddTriangle()
{
	m_output << TRIANGLE_INPUT_FORMAT;

	std::string fillColorStr, outlineColorStr;
	double x1, y1, x2, y2, x3, y3;

	if (!(m_input >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> fillColorStr >> outlineColorStr))
	{
		throw std::invalid_argument(INVALID_INPUT_FORMAT_ERROR);
	}

	if (!IsValidColorFormat(fillColorStr) || !IsValidColorFormat(outlineColorStr))
	{
		throw std::invalid_argument(INVALID_COLOR_FORMAT_ERROR);
	}

	if (GetDeterminant(CPoint(x1, y1), CPoint(x2, y2), CPoint(x3, y3)) == 0)
	{
		throw std::invalid_argument(INVALID_TRIANGLE_COORDS_ERROR);
	}

	uint32_t fillColor = ColorToInt(fillColorStr);
	uint32_t outlineColor = ColorToInt(outlineColorStr);

	auto triangle = std::make_unique<CTriangle>(CPoint(x1, y1), CPoint(x2, y2), CPoint(x3, y3), fillColor, outlineColor);
	m_shapes.push_back(std::move(triangle));
}

void ShapeController::AddLine()
{
	m_output << LINE_SEGMENT_INPUT_FORMAT;

	std::string colorStr;
	double x1, y1, x2, y2;

	if (!(m_input >> x1 >> y1 >> x2 >> y2 >> colorStr))
	{
		throw std::invalid_argument(INVALID_INPUT_FORMAT_ERROR);
	}

	if (!IsValidColorFormat(colorStr))
	{
		throw std::invalid_argument(INVALID_COLOR_FORMAT_ERROR);
	}

	uint32_t outlineColor = ColorToInt(colorStr);
	auto line = std::make_unique<CLineSegment>(CPoint(x1, y1), CPoint(x2, y2), outlineColor);
	m_shapes.push_back(std::move(line));
}

IShape* ShapeController::GetShapeWithMaxArea() const
{
	auto result = std::max_element(m_shapes.begin(), m_shapes.end(), [](auto& a, auto& b) { 
		return a->GetArea() < b->GetArea(); 
		});
	 
	if (result != m_shapes.end()) 
	{ 
		return result->get(); 
	}

	return nullptr;
}

IShape* ShapeController::GetShapeWithMinPerimeter() const
{
	auto result = std::min_element(m_shapes.begin(), m_shapes.end(), [](auto& a, auto& b) { 
		return a->GetPerimeter() < b->GetPerimeter(); 
		});

	if (result != m_shapes.end()) 
	{
		return result->get(); 
	}

	return nullptr;
}

void ShapeController::PrintTwoShapes()
{
	if (m_shapes.empty())
	{
		m_output << NO_SHAPES_MSG;
		return;
	}

	m_output << MAX_AREA_SHAPE_MSG;
	auto maxAreaShape = GetShapeWithMaxArea();
	m_output << maxAreaShape->ToString();

	m_output << MIN_PERIMETER_SHAPE_MSG;
	auto minPerimetrShape = GetShapeWithMinPerimeter();
	m_output << minPerimetrShape->ToString();
}

