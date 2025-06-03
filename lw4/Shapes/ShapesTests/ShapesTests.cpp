#define CATCH_CONFIG_MAIN
#define _USE_MATH_DEFINES
#include <math.h>
#include <catch.hpp>
#include "../lw4/Shapes/Shapes/CLineSegment.h"
#include "../lw4/Shapes/Shapes/CTriangle.h"
#include "../lw4/Shapes/Shapes/CRectangle.h"
#include "../lw4/Shapes/Shapes/CCircle.h"
#include "../lw4/Shapes/Shapes/ShapeController.h"

const uint32_t OUTLINE_COLOR = 0xffffff;
const uint32_t FILL_COLOR = 0xaaaaaa;
const double LINE_SEGMENT_LENGTH = 5.0;
const double RECT_WIDTH = 3.0;
const double RECT_HEIGHT = 4.0;
const double VALID_RADIUS = 25.0;
const double INVALID_RADIUS = -25.0;
const double TRIANGLE_AREA = 6.0;
const double TRIANGLE_PERIMETER = 12.0;

const CPoint FIRST_POS = CPoint{ 0.0, 4.0 };
const CPoint SECOND_POS = CPoint{ 3.0, 0.0 };
const CPoint THIRD_POS = CPoint{ 0.0, 0.0 };

const CPoint INVLID_FIRST_POS = CPoint{ 0.0, 0.0 };
const CPoint INVALID_SECOND_POSITION = CPoint{ 0.0, 4.0 };
const CPoint INVALID_THIRD_POS = CPoint{ 0.0, 0.0 };

const std::string INVALID_CIRCLE_INPUT = "circle 0 0.1 -3 ffffff aaaaaa";
const std::string INVALID_TRIANGLE_INPUT = "triangle 1 1 2 2 3 3 ffffff aaaaaa";
const std::string INVALID_RECTANGLE_INPUT = "rectangle 5 5 1 1 ffffff aaaaaa";
const std::string INVALID_RADIUS_CIRCLE_INPUT = "circle 0 0.1 -3 ffffff aaaaaa";
const std::string DEGENERATE_TRIANGLE_INPUT = "triangle 1 1 2 2 3 3 ffffff aaaaaa";
const std::string INVALID_VERTEXES_RECTANGLE_INPUT = "rectangle 5 5 1 1 ffffff aaaaaa";
const std::string INVALID_COLOR_SHAPE_INPUT = "rectangle 1 5 5 1 www222 123456";

const std::string LINE_SEGMENT_TEST_COMPLETION_MSG = "Line segment was created successfully!\n";
const std::string CIRCLE_TEST_COMPLETION_MSG = "Circle was created successfully!\n";
const std::string TRIANGLE_TEST_COMPLETION_MSG = "Triangle was created successfully!\n";
const std::string RECTANGLE_TEST_COMPLETION_MSG = "Rectangle was created successfully!\n";
const std::string INVALID_SHAPES_TEST_COMPLETION_MSG = "Exception for invalid input shapes is finding!\n";

TEST_CASE("Line segment tests")
{
	CLineSegment line(FIRST_POS, SECOND_POS, OUTLINE_COLOR);

	CHECK(line.GetArea() == 0);
	CHECK(line.GetStartPoint().x == FIRST_POS.x);
	CHECK(line.GetStartPoint().y == FIRST_POS.y);

	CHECK(line.GetEndPoint().x == SECOND_POS.x);
	CHECK(line.GetEndPoint().y == SECOND_POS.y);

	CHECK(line.GetArea() == 0);
	CHECK(line.GetPerimeter() == LINE_SEGMENT_LENGTH);

	CHECK(line.GetOutlineColor() == OUTLINE_COLOR);
	std::cout << LINE_SEGMENT_TEST_COMPLETION_MSG;
}

TEST_CASE("Circle tests")
{
	CCircle circle(FIRST_POS, VALID_RADIUS, FILL_COLOR, OUTLINE_COLOR); 
	CHECK(circle.GetCenter().x == FIRST_POS.x);
	CHECK(circle.GetCenter().y == FIRST_POS.y);

	CHECK(circle.GetArea() == (VALID_RADIUS * M_PI * VALID_RADIUS));
	CHECK(circle.GetPerimeter() == (2 * M_PI * VALID_RADIUS));

	CHECK(circle.GetFillColor() == FILL_COLOR);
	CHECK(circle.GetOutlineColor() == OUTLINE_COLOR);
	std::cout << CIRCLE_TEST_COMPLETION_MSG;
}

TEST_CASE("Triangle tests")
{
	CTriangle triangle(FIRST_POS, SECOND_POS, THIRD_POS, FILL_COLOR, OUTLINE_COLOR);

	CHECK(triangle.GetVertex1().x == FIRST_POS.x);
	CHECK(triangle.GetVertex1().y == FIRST_POS.y);

	CHECK(triangle.GetVertex2().x == SECOND_POS.x);
	CHECK(triangle.GetVertex2().y == SECOND_POS.y);

	CHECK(triangle.GetVertex3().x == THIRD_POS.x);
	CHECK(triangle.GetVertex3().y == THIRD_POS.y);

	CHECK(triangle.GetArea() == TRIANGLE_AREA);
	CHECK(triangle.GetPerimeter() == TRIANGLE_PERIMETER);

	CHECK(triangle.GetFillColor() == FILL_COLOR);
	CHECK(triangle.GetOutlineColor() == OUTLINE_COLOR);
	std::cout << TRIANGLE_TEST_COMPLETION_MSG;
}

TEST_CASE("Rectangle tests")
{
	CRectangle rect(FIRST_POS, SECOND_POS, FILL_COLOR, OUTLINE_COLOR);
	CHECK(rect.GetLeftTop().x == FIRST_POS.x);
	CHECK(rect.GetLeftTop().y == FIRST_POS.y);

	CHECK(rect.GetRightBottom().x == SECOND_POS.x);
	CHECK(rect.GetRightBottom().y == SECOND_POS.y);

	CHECK(rect.GetHeight() == RECT_HEIGHT);
	CHECK(rect.GetWidth() == RECT_WIDTH);

	CHECK(rect.GetArea() == RECT_HEIGHT * RECT_WIDTH);
	CHECK(rect.GetPerimeter() == 2 * (RECT_HEIGHT + RECT_WIDTH));

	CHECK(rect.GetFillColor() == FILL_COLOR);
	CHECK(rect.GetOutlineColor() == OUTLINE_COLOR);
	std::cout << RECTANGLE_TEST_COMPLETION_MSG;
}

TEST_CASE("Invalid shapes")
{
	std::istringstream input("");
	std::ostringstream output; 
	ShapeController UI(input, output);
	CHECK_THROWS_AS(UI.HandleUserInput(INVALID_RADIUS_CIRCLE_INPUT), std::invalid_argument);
	CHECK_THROWS_AS(UI.HandleUserInput(DEGENERATE_TRIANGLE_INPUT), std::invalid_argument);
	CHECK_THROWS_AS(UI.HandleUserInput(INVALID_VERTEXES_RECTANGLE_INPUT), std::invalid_argument);
	CHECK_THROWS_AS(UI.HandleUserInput(INVALID_COLOR_SHAPE_INPUT), std::invalid_argument);
	std::cout << INVALID_SHAPES_TEST_COMPLETION_MSG;
}

