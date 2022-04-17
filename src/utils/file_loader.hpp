#pragma once

#include <string>

std::string LoadFile( const std::string& path );

template<typename T, typename ... Args>
std::string LoadFile( const T& file_name, const Args&& ... args )
{
    return LoadFile(file_name) + "\n" + LoadFile( args... );
}