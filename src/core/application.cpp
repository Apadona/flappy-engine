#include "application.hpp"

CommandLineArguments::CommandLineArguments( uint32_t argc, char** argv ) : m_count(argc)
{
    for( std::uint32_t i = 0; i < m_count; ++i )
        arguments.emplace_back(argv[i]);
}

std::optional<std::string> CommandLineArguments::operator[]( uint32_t index )
{
    if( index <= m_count )
        return arguments[index];

    else
    {
        CORE_LOG_WARNING("attempted to accesss a non existence argument in command line arguments");
        return {};
    }
}
/*
WindowApplication::WindowApplication() : m_window(400,300,"window",200,200) {}

WindowApplication::WindowApplication( int16_t width, int16_t height, const std::string& title,
                                      std::int16_t pos_x, std::int16_t pos_y ) :

                                      m_title(title), m_window(width,height,m_title,pos_x,pos_y)
{

}*/