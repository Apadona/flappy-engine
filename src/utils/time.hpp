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

using clock_type = decltype( std::chrono::system_clock::now() );

using Seconds = std::chrono::seconds;
using MilliSeconds = std::chrono::milliseconds;
using MicroSeconds = std::chrono::microseconds;
using NanoSeconds = std::chrono::nanoseconds;

using TickType = long long;

class Timer
{
    public:
        Timer();

        template<typename clock_measure>
            inline TickType GetElapsedTime() const { return OperationImplemention<clock_measure>(); }

        void Reset();

    private:
        template<typename clock_measure>
            inline TickType OperationImplemention() const
            {
                return std::chrono::duration_cast<clock_measure>(ClockFunctionImpl() - m_elapsed_time).count();
            }

        clock_type ClockFunctionImpl() const;

    private:
        clock_type m_elapsed_time;
};
