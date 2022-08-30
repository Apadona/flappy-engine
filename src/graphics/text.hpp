#pragma once

#include "font_loader.hpp"

#include <maths/vector4D.hpp>

class Text
{
    public:
        Text();
        Text( const std::string& text, uint16_t pos_x, uint16_t pos_y, uint16_t size_x,
              uint16_t size_y );
        Text( const Text& other );
        Text( Text&& other );

        void SetText( const std::string& text ) { m_text = text; }
        void SetPosition( uint16_t pos_x, uint16_t pos_y ) { m_pos_x = pos_x, m_pos_y = pos_y; }
        void SetSize( uint16_t size_x, uint16_t size_y ) { m_size_x = size_x, m_size_y = size_y; }
        void SetColor( const Vec4f& color ) { m_color = color; }
        void SetFont( Font& font ) { m_font = &font; }

        const std::string& GetText() const { return m_text; }
        Vec2i GetPosition() const { return {m_pos_x,m_pos_y}; }
        Vec2i GetSize() const { return {m_size_x,m_size_y}; }
        Vec4f GetColor() { return m_color; }
        Font* GetFont() { return m_font; }

        bool IsSame( const Text& other ) const;

        Text& operator=( const std::string& text );
        Text& operator=( const Text& other );
        Text& operator=( Text&& other );

        Text operator+( const std::string& text ) const;
        Text operator+( const Text& other ) const;

        Text& operator+=( const std::string& text );
        Text& operator+=( const Text& other );

        bool operator==( const std::string& text ) const;
        bool operator==( const Text& other ) const;

        operator bool() const;
        bool operator!() const;

    private:
        std::string m_text; // TODO: must be reworked in order to support unicode characters.

        uint16_t m_pos_x;
        uint16_t m_pos_y;

        uint16_t m_size_x;
        uint16_t m_size_y;

        Vec4f m_color;

        Font* m_font;
};