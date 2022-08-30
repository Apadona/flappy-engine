#pragma once

#include "font.hpp"

#include <freetype/freetype.h>

#include <engine_pch.hpp>

#define font_path "data/fonts/"

class FontLoader
{
    friend int main( int argc, char** argv, char** env ); // so that engine can only Init/Terminate this class.

    public:
        static Font Load( const std::string& font_file_path, uint8_t width = 10, 
                          uint8_t height = 10, FontVariations variaton = FontVariations::NORMAL );

    private:
        static Font LoadFreeTypeFont( const std::string& font_file_path, uint8_t width, uint8_t height );
        static bool Init(); // initializes the underlying font library such as freetype.
        static bool Terminate(); // terminates the underlying font library such as freetype.

    private:
        static FT_Library freetype_lib;
        static FT_Face freetype_face;

        static bool initialized;
};