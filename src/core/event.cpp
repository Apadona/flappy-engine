#include "event.hpp"

Event::EventData::EventData() {}

Event::Event()
{
    Reset();
}

Event::Event( const Event& other )
{
    Reset();

    *this = other;
}

Event::Event( Event&& other )
{
    *this = std::forward<Event>(other);
}

Event& Event::operator=( const Event& other )
{
    if( this == &other )
        return *this;

    m_category = other.m_category;
    m_type = other.m_type;
    m_data = other.m_data;

    return *this;
}

Event& Event::operator=( Event&& other )
{
    m_category = other.m_category;
    m_type = other.m_type;
    m_data = other.m_data;

    other.m_category = EventCategory::NONE;
    other.m_type = EventType::NONE;
    other.m_data.null_event.null = 0;

    return *this;
}

void Event::Reset()
{
    m_category = EventCategory::NONE;
    m_type = EventType::NONE;
    m_data.null_event.null = 0;
}