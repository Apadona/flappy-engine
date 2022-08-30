#pragma once

#include "texture_atlas.hpp"

#include <maths/vector4D.hpp>

#include <freetype/freetype.h>

enum class FontVariations
{
    NORMAL,
    BOLD,
    ITALIC,
    BOLD_ITALIC
};

struct GlyphMetric
{
    //GlyphMetric()= default;
    //GlyphMetric( Vec2i size, Vec2i bearing, uint32_t advance, std::vector<uint8_t> pixels );

    Vec2ui m_size;
    Vec2ui m_bearing;
    int32_t m_advance;
    std::vector<uint8_t> m_pixels;
};

using CharacterCode = uint32_t;
using FontCharacter = std::map<CharacterCode,GlyphMetric>;
using GlyphPlaces = std::map<CharacterCode,std::uint32_t>;

class FontMap
{
    public:
        FontMap() = default;
        FontMap( const FontCharacter& font );

        void Generate( const FontCharacter& font );

        bool HasCharacter( CharacterCode code ) const;

        uint32_t GetWidth() const { return m_width; }
        uint32_t GetHeight() const { return m_height; }

    private:
        std::vector<uint8_t> ConstructImage( const FontCharacter& font ) const;
    private:

        GlyphPlaces m_places;

        std::vector<uint8_t> font_image;
        std::uint32_t m_width, m_height;
};

class FontAtlas : public TextureAtlas
{
    public:
        FontAtlas( const GlyphPlaces& places );

        Vec4f GetCharacterCoordinates( CharacterCode code ) const;

        // useful for text instance/batch rendering.
        std::vector<Vec2i> GetAllCharcterOffsetsInTexture() const;
        std::vector<Vec2i> GetAllCharacterRatiosInTexture() const;
};

class Font
{
    friend class FontLoader;

    public:
        Font();
        Font( const Font& other ) = delete;
        Font( Font&& other );

        Font& operator=( Font&& other );

        uint8_t GetSizeX() const { return m_size_x; }
        uint8_t GetSizeY() const { return m_size_y; }
        FontMap* GetMap() { return m_map; }

        operator bool() const;
        bool operator!() const;

    private:

    private:        
        uint8_t m_size_x;
        uint8_t m_size_y;

        FontCharacter m_characters;
        FontMap* m_map;
};
