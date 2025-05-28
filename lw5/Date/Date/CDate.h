#pragma once
#include <iostream> 

enum class Month
{
    JANUARY = 1, FEBRUARY, MARCH, APRIL,
    MAY, JUNE, JULY, AUGUST, SEPTEMBER,
    OCTOBER, NOVEMBER, DECEMBER
};

enum class WeekDay
{
    SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
    THURSDAY, FRIDAY, SATURDAY
};

class CDate
{
public:
    CDate(unsigned day, Month month, unsigned year);
    explicit CDate(unsigned timestamp);
    CDate();

    CDate& operator++();
    CDate operator++(int);
    CDate& operator--();
    CDate operator--(int);
    CDate operator+(int days) const;
    CDate operator-(int days) const;
    int operator-(const CDate& other) const;
    CDate& operator+=(int days);
    CDate& operator-=(int days);

    friend std::ostream& operator<<(std::ostream& stream, const CDate& date);
    friend std::istream& operator>>(std::istream& stream, CDate& date);

    bool operator== (const CDate& rhs) const;
    bool operator!= (const CDate& rhs) const;
    bool operator<= (const CDate& rhs) const;
    bool operator< (const CDate& rhs) const;
    bool operator>= (const CDate& rhs) const;
    bool operator> (const CDate& rhs) const;

    unsigned GetDay() const;
    Month GetMonth() const;
    unsigned GetYear() const;
    WeekDay GetWeekDay() const;

    bool IsValid() const;

private:
    unsigned m_timestamp;
};