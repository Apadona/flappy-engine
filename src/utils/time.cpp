#include "time.hpp"

#include <sstream>

std::ostream& operator<<( std::ostream& out, const Time& time )
{
    out << "seconds passed:" << time.day_time.m_seconds << '\n'
        << "minutes passed:" << time.day_time.m_minutes << '\n'
        << "hours passed:" << time.day_time.m_hours << '\n'
        << "day of the month:" << time.date_time.m_days_of_month << '\n'
        << "on month:" << time.date_time.m_month << '(' << time.IntToMonthStr(time.date_time.m_month) << ')'
        << "on year:" << time.date_time.m_year << '\n';

    return out;
}

Time::DateTime::DateTime() : m_days_of_month(0), m_month(0), m_year(0) {}

std::string Time::DateTime::ToString() const
{
    std::stringstream ss;
    ss << "[" << m_days_of_month << ' ' << m_month << " (" 
       << Time::IntToMonthStr(m_month) << ") "<< m_year << "]";

    return ss.str();
}

Time::DayTime::DayTime() : m_seconds(0), m_minutes(0), m_hours(0) {}

std::string Time::DayTime::ToString() const
{
    std::stringstream ss;
    ss << "[" << m_seconds << ' ' << m_minutes << ' ' << m_hours << "]";

    return ss.str();
}

Time::Time()
{
    tm now;
    mktime(&now);

    day_time.m_seconds = now.tm_sec;
    day_time.m_minutes = now.tm_min;
    day_time.m_hours = now.tm_hour;
    
    date_time.m_days_of_month = now.tm_mday;
    date_time.m_month = now.tm_mon;
    date_time.m_year = now.tm_year;
}

std::string Time::ToString() const
{
    return date_time.ToString() + " " + day_time.ToString();
}

std::string_view Time::IntToMonthStr( int month )
{
    switch( month )
    {
        case 1:
            return "January";

        case 2:
            return "February";

        case 3:
            return "March";

        case 4:
            return "April";

        case 5:
            return "May";

        case 6:
            return "June";

        case 7:
            return "July";

        case 8:
            return "August";

        case 9:
            return "September";

        case 10:
            return "October";

        case 11:
            return "November";

        case 12:
            return "December";

        default:
            CORE_LOG_ERROR("Invalid value sent for calculation month title!\n");
            return "";
    }
}

Timer::Timer()
{
    Reset();
}

void Timer::Reset()
{
    m_elapsed_time = ClockFunctionImpl();
}

clock_type Timer::ClockFunctionImpl() const
{
    return std::chrono::system_clock::now();
}
