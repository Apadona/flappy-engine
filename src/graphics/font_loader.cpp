#include "font_loader.hpp"

FT_Library FontLoader::freetype_lib;
FT_Face FontLoader::freetype_face;

bool FontLoader::initialized = false;

namespace
{
    uint32_t ClampToTheNearestGreaterPowerOfTwo( uint32_t value )
    {
        uint32_t power_of_two = 1;
        while( power_of_two < value )
            power_of_two *= 2;

        return power_of_two;
    }

    uint32_t ClampToTheNearestLowerPowerOfTwo( uint32_t value )
    {
        uint32_t power_of_two = 1;
        while( power_of_two * 2 < value )
            power_of_two *= 2;

        return power_of_two;
    }

    Vec2ui FindClosestCoupleToPowerOfTwo( uint32_t value )
    {
        uint32_t first = std::floor(std::sqrt(value));
        first = ClampToTheNearestGreaterPowerOfTwo(first);
        uint32_t second = ClampToTheNearestGreaterPowerOfTwo(first);

        return {first,second};
    }
}


bool FontLoader::Init()
{
    if( !initialized )
        if ( FT_Init_FreeType(&freetype_lib) ) // returns a non-zero value if an error accured.
            return false;

    initialized = true;

    return true;
}

Font FontLoader::Load( const std::string& font_file_path, uint8_t font_width, uint8_t font_height, uint16_t image_width,
                       uint16_t image_height, uint16_t offset_x, uint32_t offset_y )
{
    if( !initialized )
    {
        if( !Init() )
            return {};
    }

    if( !ValidateFilePath(font_file_path) )
    {
        CORE_LOG_ERROR("invalid file path sent for loading the font.");
        return {};
    }

    if( font_width == 0 )
    {
        CORE_LOG_HINT("font width for loading cannot be 0! changing to 10.");
        font_width = 10;
    }

    if( font_height == 0 )
    {
        CORE_LOG_HINT("font height for loading cannot be 0! changing to 10.");
        font_height = 10;
    }

    Font font = LoadFreeTypeFont(font_file_path,font_width,font_height);
    std::uint32_t image_size = 0;
    for( auto& c : font.m_characters )
        image_size += c.second.m_size.x * c.second.m_size.y + 4 * c.second.m_size.y;

    if( !image_width )
    {
        if( !image_height )
        {
            Vec2ui power_of_two_closeset = FindClosestCoupleToPowerOfTwo(image_size);
            image_width = power_of_two_closeset.x;
            image_height = power_of_two_closeset.y;
        }

        else
        {
            uint32_t value = image_size / image_height;
            image_width = ClampToTheNearestGreaterPowerOfTwo(value);            
        }
    }

    else if( !image_height )
    {
        uint32_t value = image_size / image_width;
        image_height = ClampToTheNearestGreaterPowerOfTwo(value);
    }

    CORE_LOG_HINT("image_width:",image_width," image_height:",image_height);

    font.GenerateImage(image_width,image_height,4,4);

    return font;
}

Font FontLoader::LoadFreeTypeFont( const std::string& font_file_path, uint8_t width, uint8_t height )
{
    if ( FT_New_Face(freetype_lib,font_file_path.c_str(),0,&freetype_face) )
    {
        CORE_LOG_ERROR("freetype failed to load the font from the file!\n");
        return {};
    }

    FT_Set_Pixel_Sizes(freetype_face,width,height);

    Font font;

    for( uint32_t character_code = 32; character_code < 128; ++character_code )
    {
        if( FT_Load_Char(freetype_face,character_code,FT_LOAD_RENDER) )
        {
            CORE_LOG_WARNING("could not load the font glyph for character:",static_cast<char>(character_code));
            continue;
        }

        auto& _glyph = freetype_face->glyph;
        GlyphMetric glyph_metric =
        {
            {static_cast<uint32_t>(_glyph->bitmap.width),static_cast<uint32_t>(_glyph->bitmap.rows)},
            {static_cast<uint32_t>(_glyph->bitmap_left),static_cast<uint32_t>(_glyph->bitmap_top)},
            static_cast<uint32_t>(_glyph->advance.x),
            {}
        };

        for( uint32_t i = 0; i < glyph_metric.m_size.x * glyph_metric.m_size.y; ++i )
            glyph_metric.m_pixels.push_back(_glyph->bitmap.buffer[i]);

        font.m_characters.insert(std::pair<uint32_t,GlyphMetric>(character_code,glyph_metric));
    }
    
    return font;
}

bool FontLoader::Terminate()
{
    if( !FT_Done_FreeType( freetype_lib ) ) // returning 0 indicates success.
        return true;

    return false;
}