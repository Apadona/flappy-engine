#pragma once

#include "font.hpp"

#include <freetype/freetype.h>

#include <engine_pch.hpp>

#define  FONT_PATH "data/fonts/"

class FontLoader
{
    friend class EngineInterface; // so that engine can only Init/Terminate this class.

    public:
        static Font Load( const std::string& font_file_path, uint8_t font_width = 10, uint8_t font_height = 10, 
                          uint16_t image_width = 0, uint16_t image_height = 0, uint16_t offset_x = 0, uint32_t offset_y = 0 );

    private:
        static Font LoadFreeTypeFont( const std::string& font_file_path, uint8_t width, uint8_t height );
        static bool Init(); // initializes the freetype font library.
        static bool Terminate(); // terminates the freetype font library.

    private:
        static FT_Library freetype_lib;
        static FT_Face freetype_face;

        static bool initialized;
};