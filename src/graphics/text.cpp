#include "text.hpp"

Text::Text() : m_text(""), m_pos_x(0), m_pos_y(0), m_size_x(0), m_size_y(0), m_font(nullptr) {}

Text::Text( const std::string& text, uint16_t pos_x, uint16_t pos_y, uint16_t size_x, uint16_t size_y ) :
            m_text(text), m_pos_x(pos_x), m_pos_y(pos_y), m_size_x(size_x), m_size_y(size_y), m_font(nullptr) {}

Text::Text( const Text& other )
{
    *this = other;
}

Text::Text( Text&& other )
{
    *this = std::forward<Text>(other);
}

bool Text::IsSame( const Text& other ) const
{
    return m_text == other.m_text && m_size_x == other.m_size_x && m_size_y == other.m_size_y &&
           m_font == other.m_font;
}

Text& Text::operator=( const std::string& other )
{
    m_text = other;
    
    return *this;
}

Text& Text::operator=( const Text& other )
{
    if( this == &other )
        return *this;

    m_text = other.m_text;
    m_pos_x = other.m_pos_x;
    m_pos_y = other.m_pos_y;
    m_size_x = other.m_size_x;
    m_size_y = other.m_size_y;
    m_color = other.m_color;
    m_font = other.m_font;

    return *this;
}

Text& Text::operator=( Text&& other )
{
    if( this == &other )
        return *this;

    m_text = std::move(other.m_text);
    m_pos_x = other.m_pos_x;
    m_pos_y = other.m_pos_y;
    m_size_x = other.m_size_x;
    m_size_y = other.m_size_y;
    m_color = other.m_color;
    m_font = other.m_font;

    return *this;
}

Text Text::operator+( const std::string& other ) const
{
    return Text(m_text + other,m_pos_x,m_pos_y,m_size_x,m_size_y);
}

Text Text::operator+( const Text& other ) const
{
    return *this + other.m_text;
}

Text& Text::operator+=( const std::string& other )
{
    m_text += other;

    return *this;
}

Text& Text::operator+=( const Text& other )
{
    return *this += other.m_text;
}

bool Text::operator==( const std::string& text ) const
{
    return m_text == text;
}

bool Text::operator==( const Text& other ) const
{
    return m_text == other.m_text;
}

Text::operator bool() const
{
    return !m_text.empty();
}

bool Text::operator!() const
{
    return m_text.empty();
}