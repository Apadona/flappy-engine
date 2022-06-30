#pragma once

#include <string>
#include <cstdint>

std::string LoadFile( const std::string& path );

template<typename T, typename ... Args>
std::string LoadFile( const T& file_name, const Args&& ... args )
{
    return LoadFile(file_name) + "\n" + LoadFile( args... );
}

bool ValidateFilePath( const std::string& file_path );

std::uint64_t GetFileSize( const std::string& file_path );
bool IsFileEmpty( const std::string& file_path );
