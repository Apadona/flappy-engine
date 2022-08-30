#include "font.hpp"
#include "font_loader.hpp"

//GlyphMetric::GlyphMetric( Vec2i size, Vec2i bearing, uint32_t advance, std::vector<uint8_t> pixels ) :
//                          m_size(size), m_bearing(bearing), m_advance(advance), m_pixels(pixels) {}

FontMap::FontMap( const FontCharacter& font )
{
    Generate(font);
}

void FontMap::Generate( const FontCharacter& font )
{
    auto font_image = ConstructImage(font);

    uint32_t place_in_texture_atlas = 0;

    auto PutCharacterRangeIntoFontMap = [&]( CharacterCode start_character, CharacterCode end_character )
    {
        for( CharacterCode character = start_character; character < end_character; ++character )
        {
            auto found = font.find(character);
            if( found != font.end() )
                m_places.emplace(character,place_in_texture_atlas++);

            auto& glyph_pixel = found->second.m_pixels;
            auto glyph_pixel_size_x = found->second.m_size.x;
            auto glyph_pixel_size_y = found->second.m_size.y;

            for( uint32_t y = 0; y < glyph_pixel_size_y; ++y )
                for( uint32_t x = 0; x < glyph_pixel_size_x; ++x )
                {
                    font_image[ x + y * glyph_pixel_size_y ] = glyph_pixel[ x + y * glyph_pixel_size_y ];
                }
        }
    };

    PutCharacterRangeIntoFontMap(65,90); // A to Z.
    PutCharacterRangeIntoFontMap(97,122); // a to z.
    PutCharacterRangeIntoFontMap(48,57); // 0 to 9.
    PutCharacterRangeIntoFontMap(40,47); // ( ) * + , - . /
    PutCharacterRangeIntoFontMap(58,64); // : ; < = > ? @
    PutCharacterRangeIntoFontMap(32,39); // space ! " # $ % & '
    PutCharacterRangeIntoFontMap(91,96); // [ \ ] ^ _ `
    PutCharacterRangeIntoFontMap(123,127); // { | } ~ delete

    /*m_font_texture.Create(TextureType::TEXTURE_2D,std::sqrt(font_image.size()),
                          std::sqrt(font_image.size()),font_image.data(),
                          TextureFormat::RED_ONLY);*/

    //m_font_atlas.SetTexture(m_font_texture,std::sqrt(m_places.size()),std::sqrt(m_places.size()),)

}

/*bool FontMap::SetCharacter( CharacterCode character_code )
{
    auto place = FindCharacterPlace(character_code);

    if( place )
    {
        //m_font_atlas.Set(place);

        return true;
    }

    return false;
}*/

bool FontMap::HasCharacter( CharacterCode character_code ) const
{
    auto place = HasCharacter(character_code);
    if( place != 0 )
        return true;

    return false;
}

/*std::uint32_t FontMap::FindCharacterPlace( CharacterCode character_code ) const
{
    auto place = m_places.find(character_code);
    if( place != m_places.end() )
        return place->second;

    return 0;
}*/

std::vector<uint8_t> FontMap::ConstructImage( const FontCharacter& font ) const
{
    if( font.empty() )
    {
        CORE_LOG_ERROR("Empty font data sent for creating FontMap!\n");
        return {};
    }

    uint32_t image_width = 0, image_height = 0;

    std::uint32_t image_size = 256; // 4 x ( 8 * 8 ) pixels for borders.
    for( auto& i : font )
        image_size += i.second.m_advance * i.second.m_size.y;

    auto _s = image_size % 4;
    if( _s )
        image_size += _s;

    std::vector<uint8_t> font_pixel_data(image_size);

    return font_pixel_data;
}

Font::Font() : m_size_x(0), m_size_y(0), m_characters(), m_map(nullptr) {}

Font::Font( Font&& other )
{
    *this = std::forward<Font>(other);
}

Font& Font::operator=( Font&& other )
{
    if( this == &other )
        return *this;

    m_size_x = other.m_size_x;
    m_size_y = other.m_size_y;
    m_characters = other.m_characters;
    m_map = other.m_map;

    other.m_size_x = 0;
    other.m_size_y = 0;
    other.m_characters.clear();
    other.m_map = nullptr;

    return *this;
}

Font::operator bool() const
{
    return m_characters.empty();
}

bool Font::operator!() const
{
    return !(m_characters.empty());
}