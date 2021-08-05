#include "file_loader.hpp"

#include <fstream>

std::string LoadFile( const std::string& file_path )
{
    std::ifstream reader(file_path.data());
    if( reader.is_open() )
    {
        reader.seekg(0,reader.end);
        std::size_t file_length = reader.tellg();
        reader.seekg(0,reader.beg);

        std::string file_content;
        std::getline(reader,file_content,'\0');
        
        return std::move(file_content);
    }

    return {};
}