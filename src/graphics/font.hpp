#pragma once

#include "texture_atlas.hpp"

#include <maths/vector4D.hpp>

#include <freetype/freetype.h>

struct GlyphMetric
{
    //GlyphMetric()= default;
    //GlyphMetric( Vec2i size, Vec2i bearing, uint32_t advance, std::vector<uint8_t> pixels );

    Vec2ui m_size;
    Vec2ui m_bearing;
    uint32_t m_advance;
    std::vector<uint8_t> m_pixels;
};

std::ostream& operator<<( std::ostream& out, const GlyphMetric& metrics );

using CharacterCode = uint32_t;
using FontCharacterInfo = std::map<CharacterCode,GlyphMetric>;
using GlyphPlaces = std::map<CharacterCode,std::int32_t>;

// this class handles the creation of a image based of a font.
class FontImage
{
    public:
        FontImage() = default;
        //FontImage( const FontImage& other );
        FontImage( FontImage&& other );
        FontImage( const FontCharacterInfo& font, uint16_t character_rows, uint16_t character_columns, uint16_t offset_x,
                   uint16_t offset_y );

        //FontImage& operator=( const FontImage& other );
        FontImage& operator=( FontImage&& other );

        void Generate( const FontCharacterInfo& font,uint16_t width, uint16_t height, uint16_t offset_x, uint16_t offset_y );

        bool operator!() const;
        operator bool() const;

        uint8_t* GetPixels() { return const_cast<uint8_t*>(m_font_image.data()); }

        uint16_t GetWidth() const { return m_width; }
        uint16_t GetHeight() const { return m_height; }

        uint16_t GetCharacterRows() const { return m_character_rows; }
        uint16_t GetCharacterColumns() const { return m_character_columns; }

        uint16_t GetImageOffsetX() const { return m_image_offset_x; }
        uint16_t GetImageOffsetY() const { return m_image_offset_y; }

    private:
        std::vector<uint8_t> m_font_image;
        std::uint16_t m_width = 0, m_height = 0;
        std::uint16_t m_character_rows = 0, m_character_columns = 0;
        std::uint16_t m_image_offset_x = 0, m_image_offset_y = 0;
};

class FontAtlas : public TextureAtlas
{
    public:
        FontAtlas() = default;
        //FontAtlas( const FontAtlas& other );
        FontAtlas( FontAtlas&& other );
        FontAtlas( FontImage& font_image );

        FontAtlas& operator=( FontAtlas&& other );

        void Generate( FontImage& font_image );

        uint32_t GetCharacterPlaceInTexture( CharacterCode code ) const;
        Vec2f GetCharacterOffsetInTexture( CharacterCode code ) const;
        Vec2f GetCharacterRatioInTexture( CharacterCode code ) const;
        Vec4f GetCharacterCoordinatesInTexture( CharacterCode code ) const;

        // useful for text instance/batch rendering.
        const std::vector<Vec2i> GetAllCharcterOffsetsInTexture() const { return m_character_offsets; }
        const std::vector<Vec2i> GetAllCharacterRatiosInTexture() const { return m_character_ratios; }
        std::vector<Vec4i> GetAllCharacterInformationsInTexture() const;

        const std::vector<Vec2i> GetAllCharacterOffsetsBasedOfTextInTexture( const std::string& character_strings ) const;
        const std::vector<Vec2i> GetAllCharacterRatiosBasedOfTextInTexture( const std::string& character_strings ) const;
        std::vector<Vec4i> GetAllCharacterInformationsBasedofTextInTexture( const std::string& character_strings ) const;

    private:
        GlyphPlaces m_places;
        std::vector<Vec2i> m_character_offsets;
        std::vector<Vec2i> m_character_ratios;
};

class Font
{
    friend class FontLoader;
    friend class Renderer;

    public:
        Font();
        //Font( const Font& other );
        Font( Font&& other );

        //Font& operator=( const Font& other );
        Font& operator=( Font&& other );

        const std::optional<GlyphMetric> GetCharacterGlyph( CharacterCode character_code ) const;

        bool HasCharacter( CharacterCode code ) const;
        bool HasImageGenerated() const;
        bool HasTextureAtlasGenerated() const;

        void GenerateImage( uint16_t character_rows, uint16_t character_columns, uint16_t offset_x, uint16_t offset_y );

        uint8_t GetSizeX() const { return m_size_x; }
        uint8_t GetSizeY() const { return m_size_y; }
        const FontImage& GetImage() const { return m_image; }
        const FontAtlas& GetAtlas() const { return m_atlas; }

        operator bool() const;
        bool operator!() const;

    private:        
        FontCharacterInfo m_characters;
        uint8_t m_size_x;
        uint8_t m_size_y;

        FontImage m_image;
        FontAtlas m_atlas;
};
