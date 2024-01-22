#include <iostream>
#include    <assert.h>

const unsigned int daysInMonth[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

class Date
{
private:

    int day_;
    int month_;
    int year_;

public:

    Date(int day, int month, int year);

    ~Date();

    void advance();

    int day();
    int month();
    int year();

    void setDay(int d);
    void set(int day, int month, int year);
};

int main(void)
{
    Date startOfTerm(6, 10, 2023);
    startOfTerm.advance();
    std::cout << startOfTerm.month() << std::endl;
    assert( startOfTerm.day() == 7 );
    assert( startOfTerm.month() == 10 );
    assert( startOfTerm.year() == 2023 );
    Date halloween(31, 10, 2023);
    halloween.advance();
    assert( halloween.day() == 1 );
    assert( halloween.month() == 11 );
    assert( halloween.year() == 2023 );
    /* This should fail (exit) at run−time because
    // there is no 31st November. */
    //halloween.setDay(31);
    halloween.set(31, 10, 2023); // This should succeed
    // /* This should fail (exit) at run−time because
    // there is no 31st November. */
    // halloween.setMonth(11);
    // Date startOfYear(1, 1, 2024);
    // startOfYear.back();
    // assert( startOfYear.day() == 31 );
    // assert( startOfYear.month() == 12 );
    // assert( startOfYear.year() == 2023 );
    // const Date endOfYear = startOfYear;
    // assert(endOfYear.day() == 31);
    // endOfYear.setMonth(10); // Should fail at *compile−time*
    // endOfYear = halloween; // Should fail at *compile−time*
}



Date::Date(int day, int month, int year)
{
    day_ = day;
    month_ = month;
    year_ = year;
}

Date::~Date()
{
}

void Date::advance() 
{
    if (day_ < daysInMonth[month_])
    {
        day_ += 1;
    }
    else if (day_== daysInMonth[month_])
    {
        day_ = 1;
        month_ += 1; 
    }
    
    //month_ = month_;
    //year_ = year; 
}

int Date::day()
{
    return day_;
}
int Date::month()
{
    return month_;
}
int Date::year()
{
    return year_;
}

void Date::setDay(int d)
{
    assert( d <= daysInMonth[month_] );
    day_ = d;
}

void Date::set(int day, int month, int year)
{
    assert( day <= daysInMonth[month] );
    day_ = day;
    assert( month <= 12 );
    month_ = month;
}

