#include "font.hpp"
#include "font_loader.hpp"

#include <graphics/texture_manager.hpp>

namespace
{
    template<typename T>
    void FlipImageVertically( std::vector<T>& image, uint32_t width, uint32_t height )
    {
        if( image.empty() || height == 0 )
            return;

        auto size = width * height;
        if( image.size() != size )
        {
            CORE_LOG_ERROR("size of the image which is sent for fliping vertically is not equal to sizes provided!");
            return;
        }

        for( uint32_t j = 1; j < height / 2; j++ )
        {
            for( uint32_t i = 0; i < width; ++i )
            {
                auto temp = image[i + j * width];
                image[i + (j - 1) * width] = image[i + (height - j) * width];
                image[i + (height - j) * width] = temp;
            }
        }
    }
}

//GlyphMetric::GlyphMetric( Vec2i size, Vec2i bearing, uint32_t advance, std::vector<uint8_t> pixels ) :
//                          m_size(size), m_bearing(bearing), m_advance(advance), m_pixels(pixels) {}

std::ostream& operator<<( std::ostream& out, const GlyphMetric& metric )
{
    out << "width:" << metric.m_size.x << " height:" << metric.m_size.y << " m_advance:" << metric.m_advance
        << " bearing_width:" << metric.m_bearing.x << " bearing_height:" << metric.m_bearing.y << " pixels:" << std::endl;

    for( uint32_t j = 0; j < metric.m_size.y; ++j )
    {
        for( uint32_t x = 0; x < metric.m_size.x; ++x )
            out <<
            ((static_cast<int>(metric.m_pixels[x + j * metric.m_size.y ]) < 50)? " " : "*");
            /*metric.m_pixels[x + j * metric.m_size.y ]*/
                /*<< ' ';*/

        out << std::endl;
    }

    return out;
}

/*FontImage::FontImage( const FontImage& other )
{
    *this = other;
}*/

FontImage::FontImage( FontImage&& other )
{
    *this = std::forward<FontImage>(other);
}

FontImage::FontImage( const FontCharacterInfo& font, uint16_t character_rows, uint16_t character_columns, uint16_t offset_x,
                   uint16_t offset_y )
{
    Generate(font,character_rows,character_columns,offset_x,offset_y);
}

/*FontImage& FontImage::operator=( const FontImage& other )
{
    if( this == &other )
        return *this;
    
    m_width = other.m_width, m_height = other.m_height;
    m_character_rows = other.m_character_rows, m_character_columns = other.m_character_columns;
    m_image_offset_x = other.m_image_offset_x, m_image_offset_y = other.m_image_offset_y;
    m_font_image = other.m_font_image;

    return *this;
}*/

FontImage& FontImage::operator=( FontImage&& other )
{
    if( this == &other )
        return *this;

    m_width = other.m_width, m_height = other.m_height;
    m_character_rows = other.m_character_rows, m_character_columns = other.m_character_columns;
    m_image_offset_x = other.m_image_offset_x, m_image_offset_y = other.m_image_offset_y;
    m_font_image = std::move(other.m_font_image);

    other.m_width = 0, other.m_height = 0;
    other.m_character_rows = 0, other.m_character_columns = 0;
    other.m_image_offset_x = 0, other.m_image_offset_y = 0;

    return *this;
}

void FontImage::Generate( const FontCharacterInfo& font,uint16_t image_width, uint16_t image_height, uint16_t offset_x,
                          uint16_t offset_y )
{
    if( font.empty() )
    {
        CORE_LOG_ERROR("Empty font data sent for creating FontImage!\n");
        return;
    }

    bool currect_measures = true;
    if( !image_width )
    {
        CORE_LOG_ERROR("cannot generate a font image with a width of 0!");
        currect_measures = false;
    }

    if( !image_height )
    {
        CORE_LOG_ERROR("cannot generate a font image with a height of 0!");
        currect_measures = false;
    }

    if( !currect_measures )
        return;

    m_width = image_width;
    m_height = image_height;

    uint32_t image_size = static_cast<uint32_t>(m_width) * static_cast<uint32_t>(m_height);

    CORE_LOG_HINT("font image_size is:",image_size);

    m_font_image.resize(image_size,127);

    std::uint16_t draw_position_x = offset_x, draw_position_y = offset_y;
    std::uint16_t temp_x = draw_position_x, temp_y = draw_position_y;

    auto PutCharacterRangeIntoFontImage = [&]( CharacterCode start_character, CharacterCode end_character )
    {
        for( CharacterCode character = start_character; character <= end_character; ++character )
        {
            auto found = font.find(character);
            if( found == font.end() )
            {
                CORE_LOG_ERROR("Was unable to find font character ",character," in the specified font for making it's image!");
                continue;
            }

            auto& metric = found->second;

            auto& glyph_pixel = metric.m_pixels;
            auto glyph_pixel_size_x = metric.m_size.x;
            auto glyph_pixel_size_y = metric.m_size.y;

            if( m_width < temp_x + glyph_pixel_size_x )
            {
                temp_x = offset_x;
                temp_y = draw_position_y + 8;
            }

            draw_position_x = temp_x;
            draw_position_y = temp_y;

            for( uint16_t y = 0; y < glyph_pixel_size_y; ++y )
            {
                for( uint16_t x = 0; x < glyph_pixel_size_x; ++x )
                {
                    m_font_image[ draw_position_x + draw_position_y * m_width ] = glyph_pixel[ x + y * glyph_pixel_size_y ];
                    ++draw_position_x;
                }

                draw_position_x = temp_x;
                ++draw_position_y;
            }

            temp_x += glyph_pixel_size_x + 4;
        }
    };

    PutCharacterRangeIntoFontImage(65,65); // A to Z.
    //PutCharacterRangeIntoFontImage(97,122); // a to z.
    //PutCharacterRangeIntoFontImage(48,57); // 0 to 9.
    //PutCharacterRangeIntoFontImage(40,47); // ( ) * + , - . /
    //PutCharacterRangeIntoFontImage(58,64); // : ; < = > ? @
    //PutCharacterRangeIntoFontImage(32,39); // space ! " # $ % & '
    //PutCharacterRangeIntoFontImage(91,96); // [ \ ] ^ _ `
    //PutCharacterRangeIntoFontImage(123,127); // { | } ~ delete

    // because OpenGL y coordinate starts at bottom left instead of the top left. 
    FlipImageVertically(m_font_image,image_width,image_height);
}

bool FontImage::operator!() const
{
    return m_font_image.empty();
}

FontImage::operator bool() const
{
    return !(m_font_image.empty());
}

FontAtlas::FontAtlas( FontImage& font_image )
{
    Generate(font_image);
}

FontAtlas::FontAtlas( FontAtlas&& other )
{
    *this = std::forward<FontAtlas>(other);
}

FontAtlas& FontAtlas::operator=( FontAtlas&& other )
{
    if( this != &other )
    {
        m_current_index = other.m_current_index;

        m_texture = other.m_texture;

        m_count_x = other.m_count_x;
        m_count_y = other.m_count_y;
        m_total_textures = other.m_total_textures;

        m_size_x = other.m_size_x;
        m_size_y = other.m_size_y;

        m_advance_x = other.m_advance_x;
        m_advance_y = other.m_advance_y;

        m_filters = std::move(other.m_filters);
        m_filter_flag = other.m_filter_flag;
    }

    other.m_current_index = 0;

    other.m_texture = nullptr;


    other.m_count_x = 0;
    other.m_count_y = 0;
    other.m_total_textures = 0;

    other.m_size_x = 0;
    other.m_size_y = 0;

    other.m_advance_x = 0;
    other.m_advance_y = 0;

    other.m_filter_flag = false;

    return *this;
}

void FontAtlas::Generate( FontImage& font_image )
{
    bool can_generate = true;
    if( !font_image )
    {
        can_generate = false;
        CORE_LOG_ERROR("cannot generate a Font Texture Atlas from an invalid image!");
    }

    //if( places.empty() )
    //{
        //can_generate = false;
        //CORE_LOG_ERROR("cannot generate a Font Texture Atlas from an empty GlyphPlaces!");
    //}

    if( can_generate )
    {
        m_texture = new Texture(TextureType::TEXTURE_2D,font_image.GetWidth(),font_image.GetHeight(),
                              font_image.GetPixels(),TextureFormat::RED_ONLY);
        //SetTexture(*p_texture,1,1,64,64,1,0,0);
    }
}

uint32_t FontAtlas::GetCharacterPlaceInTexture( CharacterCode code ) const
{
    auto find = m_places.find(code);
    if( find != m_places.end() )
        return find->second;

    return -1;
}

std::vector<Vec4i> FontAtlas::GetAllCharacterInformationsInTexture() const
{
    std::vector<Vec4i> infos(m_character_offsets.size());

    for( auto offsets : m_character_offsets )
        for( auto ratios : m_character_ratios )
            infos.emplace_back(offsets.x,offsets.y,ratios.x,ratios.y);

    return infos;
}

Font::Font() : m_characters(), m_size_x(0), m_size_y(0) {}

/*Font::Font( const Font& other )
{
    *this = other;
}*/

Font::Font( Font&& other )
{
    *this = std::forward<Font>(other);
}

const std::optional<GlyphMetric> Font::GetCharacterGlyph( CharacterCode character_code ) const
{
    auto find = m_characters.find(character_code);
    if( find != m_characters.end() )
        return find->second;

    CORE_LOG_ERROR("could not find character",character_code,"in the font!");
    return {};
}

bool Font::HasCharacter( CharacterCode character_code ) const
{
    return m_characters.find(character_code) != m_characters.end();
}

bool Font::HasImageGenerated() const
{
    return m_image;
}

bool Font::HasTextureAtlasGenerated() const
{
    return m_atlas;
}

void Font::GenerateImage( uint16_t image_width, uint16_t image_height, uint16_t offset_x, uint16_t offset_y )
{
    m_image.Generate(m_characters,image_width,image_height,offset_x,offset_y);
    m_atlas.Generate(m_image);
}

/*Font& Font::operator=( const Font& other )
{
    if( this == &other )
        return *this;

    m_size_x = other.m_size_x, m_size_y = other.m_size_y;
    m_characters = other.m_characters;
    m_image = other.m_image;
    m_atlas = other.m_atlas;
}*/

Font& Font::operator=( Font&& other )
{
    if( this != &other )
    {
        m_size_x = other.m_size_x;
        m_size_y = other.m_size_y;
        m_characters = std::move(other.m_characters);
        m_image = std::move(other.m_image);
        m_atlas = std::move(other.m_atlas);

        other.m_size_x = 0, other.m_size_y = 0;
    }

    return *this;
}

Font::operator bool() const
{
    return !m_characters.empty();
}

bool Font::operator!() const
{
    return m_characters.empty();
}