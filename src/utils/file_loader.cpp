#include "file_loader.hpp"

#include <fstream>

std::string LoadFile( const std::string& file_path )
{
    std::ifstream reader(file_path.data());
    if( reader.is_open() )
    {
        std::string file_content;
        std::getline(reader,file_content,'\0');

        reader.close();
        
        return std::move(file_content);
    }

    return {};
}

bool ValidateFile( const std::string& file_path )
{
    // TODO:must find a better way to validate file (using the OS API or filesystem API)
    std::ifstream reader(file_path.data());
    if( reader.is_open() )
    {
        reader.close();
        return true;
    }

    return false;
}

std::uint64_t GetFileSize( const std::string& file_path )
{
    
    std::ifstream reader(file_path.data());
    if( reader.is_open() )
    {
        std::uint64_t file_length;

        reader.seekg(0,reader.end);
         file_length = reader.tellg();
        reader.seekg(0,reader.beg);

        return file_length;
    }

    return 0;
}

bool IsFileEmpty( const std::string& file_path )
{
    return GetFileSize(file_path) == 0;
}