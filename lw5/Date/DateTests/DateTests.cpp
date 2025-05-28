#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "../lw5/Date/Date/CDate.h"

const unsigned YEAR_DAYS = 365;
const unsigned MAX_DAYS = 2932897;

TEST_CASE("Create date")
{
	CDate date1;
	CHECK(date1.GetYear() == 1970);
	CHECK(date1.GetMonth() == Month::JANUARY);
	CHECK(date1.GetDay() == 1);
	CDate date2(31);
	CHECK(date2.GetYear() == 1970);
	CHECK(date2.GetMonth() == Month::FEBRUARY);
	CHECK(date2.GetDay() == 1);
	CDate date3(31, Month::MAY, 2025);
	CHECK(date3.IsValid());
	CHECK(date3.GetYear() == 2025);
	CHECK(date3.GetMonth() == Month::MAY);
	CHECK(date3.GetDay() == 31);
	CHECK(date3.GetWeekDay() == WeekDay::SATURDAY);

	CDate invalidDate1(13, static_cast<Month>(13), 2025);
	CHECK_FALSE(invalidDate1.IsValid());
	CDate invalidDate2(45, Month::APRIL, 2025);
	CHECK_FALSE(invalidDate2.IsValid());
	CDate invalidDate3(MAX_DAYS + 1);
	CHECK_FALSE(invalidDate3.IsValid());
}

TEST_CASE("Leap year")
{
	CDate date1(29, Month::FEBRUARY, 2004);
	CHECK(date1.IsValid());
	CHECK(date1.GetYear() == 2004);
	CHECK(date1.GetMonth() == Month::FEBRUARY);
	CHECK(date1.GetDay() == 29);

	CDate date2(29, Month::FEBRUARY, 2100);
	CHECK_FALSE(date2.IsValid());

	CDate date3(28, Month::FEBRUARY, 2016);
	date3++;
	CHECK(date3.GetYear() == 2016);
	CHECK(date3.GetMonth() == Month::FEBRUARY);
	CHECK(date3.GetDay() == 29);
	date3 += YEAR_DAYS;
	CHECK(date3.GetYear() == 2017);
	CHECK(date3.GetMonth() == Month::MARCH);
	CHECK(date3.GetDay() == 1);
}

TEST_CASE("Dates compare")
{
	CDate date1(23, Month::APRIL, 2001);
	CDate date2(23, Month::APRIL, 2001); 
	CDate date3(3, Month::MARCH, 2001);

	CHECK(date1 == date2);
	CHECK(date1 != date3);
	CHECK(date1 <= date2);
	CHECK(date1 >= date2);
	CHECK(date1 > date3);
	CHECK(date3 < date2);
	CHECK(date1 >= date3);
	CHECK(date3 <= date2);
}

TEST_CASE("Arithmetic operations")
{
	CDate date1;
	CDate date2 = date1 + 2;
	CHECK(date2.GetDay() == 3);
	date2++;
	CHECK(date2.GetDay() == 4);
	date2 -= 2;
	CHECK(date2.GetDay() == 2);
	date2--;
	CHECK(date1 == date2);
	date1 += 32;
	CHECK(date1.GetMonth() == Month::FEBRUARY);
	CHECK(date1 - date2 == 32);
	CHECK(date2 - date1 == -32);
}

TEST_CASE("Date input/output")
{
	CDate date1;
	std::istringstream input("12.4.2020");
	input >> date1;
	CHECK(date1.IsValid());
	CHECK(date1.GetYear() == 2020);
	CHECK(date1.GetMonth() == Month::APRIL);
	CHECK(date1.GetDay() == 12);

	CDate date2;
	std::istringstream invalidInput("12.2020");
	input >> date2;
	CHECK(input.fail());

	std::ostringstream(output);
	output << date1;
	CHECK(output.str() == "12.04.2020\n");
	output.str("");
	output << date2;
	CHECK(output.str() == "01.01.1970\n");
}