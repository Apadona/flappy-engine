#include "logger.hpp"

#ifdef __WIN32
    #include <windows.h>
    #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

// because WIN32 defines an ERROR macro!
#ifdef ERROR
    #undef ERROR
#endif

#include <cstring>

const std::string_view Logger::m_escape_sequence_begin = "\x1b[";
const std::string_view Logger::m_escape_sequence_end = "\x1b[0m";

const std::vector<ColorCodes> Logger::m_color_codes =
{
    { std::to_string(static_cast<int>(BLACK)), BLACK },
    { std::to_string(static_cast<int>(RED)), RED },
    { std::to_string(static_cast<int>(GREEN)), GREEN },
    { std::to_string(static_cast<int>(YELLOW)), YELLOW },
    { std::to_string(static_cast<int>(BLUE)), BLUE },
    { std::to_string(static_cast<int>(MAGENTA)), MAGENTA },
    { std::to_string(static_cast<int>(CYAN)), CYAN },
    { std::to_string(static_cast<int>(WHITE)), WHITE },

    { std::to_string(static_cast<int>(BRIGHT_BLACK)), BRIGHT_BLACK },
    { std::to_string(static_cast<int>(BRIGHT_RED)), BRIGHT_RED },
    { std::to_string(static_cast<int>(BRIGHT_GREEN)), BRIGHT_GREEN },
    { std::to_string(static_cast<int>(BRIGHT_YELLOW)), BRIGHT_YELLOW },
    { std::to_string(static_cast<int>(BRIGHT_BLUE)), BRIGHT_BLUE },
    { std::to_string(static_cast<int>(BRIGHT_MAGENTA)), BRIGHT_MAGENTA },
    { std::to_string(static_cast<int>(BRIGHT_CYAN)), BRIGHT_CYAN },
    { std::to_string(static_cast<int>(BRIGHT_WHITE)), BRIGHT_WHITE }
};

bool Logger::Init()
{
    bool result = true;

    std::ios::sync_with_stdio(false);

    // for windows, these functions should be called so that the ansi escape codes could be supported.
    #ifdef __WIN32
        DWORD mode;
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleMode(handle,&mode);
        result = SetConsoleMode(handle,mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    #endif

    return result;
}

Logger::Logger() : m_out_memory(nullptr)
{
    SetSink(SinkType::CONSOLE,nullptr,nullptr);
    SetType(LogType::APPLICATION);

    InitLogLevelColors();
}

Logger::Logger( SinkType place, LogType type, char* dump_memory, char* dump_file )
{
    SetSink(place,dump_memory,dump_file);
    SetType(type);

    InitLogLevelColors();
}

Logger::~Logger()
{
    m_out_file.close();
}

void Logger::SetSink( SinkType type, char* dump_memory, char* dump_file )
{
    m_place = type;

    if( m_place == SinkType::FILE )
    {
        m_out_file.open(dump_file,std::ios::out | std::ios::ate);
        m_out_memory = nullptr;
    }

    else if( m_place == SinkType::MEMORY )
    {
        m_out_memory = dump_memory;
        if( m_out_file.is_open() )
        {
            m_out_file.flush();
            m_out_file.close();
        }
    }

    else // SinkType::Console
    {
        m_out_memory = nullptr;
        if( m_out_file.is_open() )
        {
            m_out_file.flush();
            m_out_file.close();
        }
    }
}

void Logger::SetType( LogType type )
{
    m_type = type;
}

void Logger::SetLogLevelColor( LogLevel level, Color color )
{
    m_level_colors[ static_cast<int>(level) ].color = color;
}

void Logger::Log( const std::string& message, LogLevel level )
{
    if( message.empty() )
        return;

    const char* level_str;

    switch( m_place )
    {
        case SinkType::MEMORY:
            level_str = LevelToStr(level);
            std::strcat(m_out_memory,level_str);
            std::strcat(m_out_memory,message.c_str());
            std::strcat(m_out_memory,"\n");
        break;

        case SinkType::FILE:
            level_str = LevelToStr(level);
            m_out_file << level_str << message << std::endl;
        break;

        case SinkType::CONSOLE:
            level_str = LevelToStr(level);
            std::clog << m_escape_sequence_begin << m_color_codes[ m_level_colors[ static_cast<int>(level) ].color ].str
                      << level_str << message << m_escape_sequence_end << std::endl;
        break;

        default:
            std::cerr << "sink place not recognised!\n";
    }
}

void Logger::InitLogLevelColors()
{
    m_level_colors =
    {
        { LogLevel::NORMAL, WHITE },
        { LogLevel::HINT, GREEN },
        { LogLevel::WARNING, YELLOW },
        { LogLevel::ERROR, RED },
        { LogLevel::DEBUG, BLUE }
    };
}

const char* Logger::LevelToStr( LogLevel level )
{
    switch( level )
        {
            case LogLevel::NORMAL:
                return "[Normal]:";
            break;

            case LogLevel::HINT:
                return "[Hint]:";
            break;

            case LogLevel::WARNING:
                return "[Warning]:";
            break;

            case LogLevel::ERROR:
                return "[Error]:";
            break;

            case LogLevel::DEBUG:
                return "[Debug]:";
            break;
        }
}