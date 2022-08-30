#include "font_loader.hpp"

FT_Library FontLoader::freetype_lib;
FT_Face FontLoader::freetype_face;

bool FontLoader::initialized = false;


bool FontLoader::Init()
{
    if( !initialized )
        if ( FT_Init_FreeType(&freetype_lib) ) // returns a non-zero value if an error accured.
            return false;

    initialized = true;

    return true;
}

Font FontLoader::Load( const std::string& font_file_path, uint8_t width, uint8_t height,
                       FontVariations variaton )
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

    if( width == 0 )
    {
        CORE_LOG_HINT("font width for loading cannot be 0! changing to 10.");
        width = 10;
    }

    if( height == 0 )
    {
        CORE_LOG_HINT("font height for loading cannot be 0! changing to 10.");
        height = 10;
    }

    Font font = LoadFreeTypeFont(font_file_path,width,height);

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
            {_glyph->bitmap.width,_glyph->bitmap.rows},
            {_glyph->bitmap_left,_glyph->bitmap_top},
            _glyph->advance.x,
            {}
        };

        for( int i = 0; i < _glyph->bitmap.width * _glyph->bitmap.rows; ++i )
            glyph_metric.m_pixels.push_back(_glyph->bitmap.buffer[i]);

        font.m_characters.insert(std::pair<uint32_t,GlyphMetric>(character_code,glyph_metric));
    }

    font.m_map = new FontMap(font.m_characters);

    return font;
}

bool FontLoader::Terminate()
{
    if( !FT_Done_FreeType( freetype_lib ) ) // returning 0 indicates success.
        return true;

    return false;
}