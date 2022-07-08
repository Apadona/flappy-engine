#pragma once

#include <string>
#include <string_view>
#include <iostream>

// a simple abstraction for strcut tm in C library.
// TODO: it should be improved a lot.
struct Time
{
    struct DateTime
    {
        DateTime();

        std::string ToString() const;

        int m_days_of_month;
        int m_month;
        int m_year;
    };

    struct DayTime
    {
        DayTime();

        std::string ToString() const;

        int m_seconds;
        int m_minutes;
        int m_hours;
    };

    Time();

    // appends DateTime to DayTime.
    std::string ToString() const;

    static std::string_view IntToMonthStr( int month );

    DateTime date_time;
    DayTime day_time;
};

std::ostream& operator<<( std::ostream& os, const Time& time );