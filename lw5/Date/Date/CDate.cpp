#include "CDate.h"

#include <map>

const std::map<Month, std::pair<unsigned, unsigned>> DAYS_IN_MONTHS
{
	{Month::JANUARY, {1, 31}},
	{Month::FEBRUARY, {32, 59}},
	{Month::MARCH, {60, 90}},
	{Month::APRIL, {91, 120}},
	{Month::MAY, {121, 151}},
	{Month::JUNE, {152, 181}},
	{Month::JULY, {182, 212}},
	{Month::AUGUST, {213, 243}},
	{Month::SEPTEMBER, {244, 273}},
	{Month::OCTOBER, {274, 304}},
	{Month::NOVEMBER, {305, 334}},
	{Month::DECEMBER, {335, 365}}
};
const unsigned MIN_YEAR = 1970;
const unsigned FIRST_LEAP_YEAR = 1972;
const unsigned MAX_YEAR = 9999;
const unsigned MAX_DAYS = 2932897;
const unsigned LEAP_YEAR_FEBRUARY_DAYS = 29;
const unsigned LEAP_YEAR_DAYS = 366;
const unsigned YEAR_DAYS = 365;
const unsigned LEAP_YEAR_PERIOD = 4;
const unsigned CENTURY = 100;
const unsigned FOUR_CENTURYS = 400;
const std::string INVALID_DATE_MSG = "INVALID DATE";

bool  IsLeapYear(unsigned year)
{
	return(year % LEAP_YEAR_PERIOD == 0 && year % CENTURY != 0) || (year % FOUR_CENTURYS == 0);
}

unsigned GetLeapYearsNumbers(unsigned year)
{
	return  year / LEAP_YEAR_PERIOD - year / CENTURY + year / FOUR_CENTURYS;
}

unsigned GetDaysInMonth(Month month, unsigned year)
{
	if (IsLeapYear(year) && month == Month::FEBRUARY)
	{
		return LEAP_YEAR_FEBRUARY_DAYS;
	}
	return DAYS_IN_MONTHS.at(month).second - DAYS_IN_MONTHS.at(month).first + 1;
}

unsigned GetDaysFromDMY(unsigned day, Month month, unsigned year)
{
	if (year < MIN_YEAR || year > MAX_YEAR  
		||   month < Month::JANUARY || month > Month::DECEMBER 
		|| day < 1 || day > GetDaysInMonth(month, year))
	{
		return MAX_DAYS + 1;
	}
	int leapYears = GetLeapYearsNumbers(year) - GetLeapYearsNumbers(MIN_YEAR);
	unsigned daysInYears = YEAR_DAYS * (year - MIN_YEAR) + leapYears;
	unsigned daysInMonths = DAYS_IN_MONTHS.at(month).first - 1;

	return daysInYears + daysInMonths + day - 1;
}

CDate::CDate(unsigned day, Month month, unsigned year)
	:m_timestamp(GetDaysFromDMY(day, month, year))
{
}

CDate::CDate(unsigned timestamp)
	: m_timestamp(timestamp)
{
}

CDate::CDate()
	: m_timestamp(0)
{
}

CDate& CDate::operator++()
{
	if (IsValid())
	{
		++m_timestamp;
	}
	return *this;
}

CDate CDate::operator++(int)
{
	CDate dateCopy = *this;
	++(*this);
	return dateCopy;
}

CDate& CDate::operator--()
{
	if (IsValid())
	{
		--m_timestamp;
	}
	return *this;
}

CDate CDate::operator--(int)
{
	CDate dateCopy = *this;
	--(*this);
	return dateCopy;
}

CDate CDate::operator+(int days) const
{
	if (IsValid())
	{
		return CDate(m_timestamp + days);
	}
	return CDate(MAX_DAYS + 1);
}

CDate CDate::operator-(int days) const
{
	if (IsValid() && static_cast<int>(m_timestamp) >= days)
	{
		return CDate(m_timestamp - days);
	}
	return CDate(MAX_DAYS + 1);
}

int CDate::operator-(const CDate& other) const
{
	return m_timestamp - other.m_timestamp;
}

CDate& CDate::operator+=(int days)
{
	if (IsValid())
	{
		m_timestamp += days;
	}

	return *this;
}

CDate& CDate::operator-=(int days)
{
	if (IsValid() && static_cast<int>(m_timestamp) >= days)
	{
		m_timestamp -= days;
	}
	else
	{
		m_timestamp = MAX_DAYS + 1;
	}

	return *this;
}

bool CDate::operator==(const CDate& other) const
{
	return m_timestamp == other.m_timestamp;
}

bool CDate::operator!=(const CDate& other) const
{
	return m_timestamp != other.m_timestamp;
}

bool CDate::operator<=(const CDate& other) const
{
	return m_timestamp <= other.m_timestamp;
}

bool CDate::operator<(const CDate& other) const
{
	return m_timestamp < other.m_timestamp;
}

bool CDate::operator>=(const CDate& other) const
{
	return m_timestamp >= other.m_timestamp;
}

bool CDate::operator>(const CDate& other) const
{
	return m_timestamp > other.m_timestamp; 
}

unsigned CDate::GetDay() const
{
	unsigned year = GetYear();
	Month month = GetMonth();
	int leapYears = GetLeapYearsNumbers(year) - GetLeapYearsNumbers(MIN_YEAR);
	unsigned daysInYears = YEAR_DAYS * (year - MIN_YEAR) + leapYears;
	unsigned daysInMonths = DAYS_IN_MONTHS.at(month).first - 1;

	return m_timestamp - (daysInYears + daysInMonths) + 1;
}

Month CDate::GetMonth() const
{
	unsigned year = GetYear();
	int leapYears = GetLeapYearsNumbers(year) - GetLeapYearsNumbers(MIN_YEAR);
	unsigned daysInYears = YEAR_DAYS * (year - MIN_YEAR) + leapYears;
	unsigned remainder = m_timestamp - daysInYears + 1;

	for (const auto& pair : DAYS_IN_MONTHS) 
	{
		if (IsLeapYear(year) && pair.first == Month::FEBRUARY
			&& pair.second.first <= remainder && remainder <= pair.second.second + 1)
		{
			return pair.first;
		}
		if (IsLeapYear(year) && pair.first == Month::MARCH)
		{
			remainder--;
		}
		if (pair.second.first <= remainder && remainder <= pair.second.second)
		{
			return pair.first;
		}
	}
}

unsigned CDate::GetYear() const
{
	if (m_timestamp >= (2 * YEAR_DAYS + LEAP_YEAR_DAYS))
	{
		unsigned remainder = m_timestamp - (2 * YEAR_DAYS + LEAP_YEAR_DAYS);
		unsigned fourCenturiesNum = remainder / (FOUR_CENTURYS * YEAR_DAYS + GetLeapYearsNumbers(FOUR_CENTURYS));
	    remainder %= (FOUR_CENTURYS * YEAR_DAYS + GetLeapYearsNumbers(FOUR_CENTURYS));
		unsigned centuriesNum = remainder / (CENTURY * YEAR_DAYS + GetLeapYearsNumbers(CENTURY));
		remainder %= (CENTURY * YEAR_DAYS + GetLeapYearsNumbers(CENTURY));
		unsigned fourYearsNum = remainder / (LEAP_YEAR_PERIOD * YEAR_DAYS + 1);
		remainder %= (LEAP_YEAR_PERIOD * YEAR_DAYS + 1);
		unsigned yearsNum = remainder / YEAR_DAYS;
		return FIRST_LEAP_YEAR + 1 + fourCenturiesNum * FOUR_CENTURYS + centuriesNum * CENTURY + fourYearsNum * LEAP_YEAR_PERIOD + yearsNum;
	}
	switch (m_timestamp / YEAR_DAYS)
	{
		case(0):
			return MIN_YEAR;
		case(1):
			return MIN_YEAR + 1;
		case(2):
			return MIN_YEAR + 2;
	}
}

WeekDay CDate::GetWeekDay() const
{
	return static_cast<WeekDay>((m_timestamp + 4) % 7);
}

bool CDate::IsValid() const
{
	return m_timestamp <= MAX_DAYS;
}

std::ostream& operator<<(std::ostream& output, const CDate& date)
{
	if (!date.IsValid())
	{
		output << INVALID_DATE_MSG;
	}
	else
	{
		unsigned day = date.GetDay();
		Month month = date.GetMonth();
		unsigned year = date.GetYear();

		output << (day < 10 ? "0" : "") << day << "."
			<< (static_cast<unsigned>(month) < 10 ? "0" : "") << static_cast<unsigned>(month) << "."
			<< year << "\n";
	}

	return output;
}

std::istream& operator>>(std::istream& input, CDate& date)
{
	unsigned day, month, year;
	char dot1, dot2;
	input >> day >> dot1 >> month >> dot2 >> year;

	if (input.fail())
	{
		return input;
	}

	date.m_timestamp = GetDaysFromDMY(day, static_cast<Month>(month), year);
	
	return input;
}
