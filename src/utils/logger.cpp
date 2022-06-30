#include "logger.hpp"

#ifdef __WIN32
    #include <windows.h>
    #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

// because WIN32 defines an ERROR macro!
#ifdef ERROR
    #undef ERROR
#endif

const std::string_view Logger::m_escape_sequence_begin = "\x1b[";
const std::string_view Logger::m_escape_sequence_end = "\x1b[0m";

Logger Logger::logger;

std::map<Color,std::string> Logger::m_color_codes =
{
    { BLACK, "30m" },
    { RED, "31m" },
    { GREEN, "32m" },
    { YELLOW, "33m" },
    { BLUE, "34m" },
    { MAGENTA, "35m" },
    { CYAN, "36m" },
    { WHITE, "37m" },

    { BRIGHT_BLACK, "90m" },
    { BRIGHT_RED, "91m" },
    { BRIGHT_GREEN, "92m" },
    { BRIGHT_YELLOW, "93m" },
    { BRIGHT_BLUE, "94m" },
    { BRIGHT_MAGENTA, "95m" },
    { BRIGHT_CYAN, "96m" },
    { BRIGHT_WHITE, "97m" }
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

void Logger::SetFlags( LoggerFlags flags, bool set )
{
    if( set )
         m_flags |= static_cast<int>(flags);

    else
        m_flags |= ~static_cast<int>(flags);
}

bool Logger::HasFlags( LoggerFlags flags )
{
    return m_flags & static_cast<int>(flags);
}

void Logger::SetLogLevelColor( LogLevel level, Color color )
{
    m_level_colors[ static_cast<int>(level) ].color = color;
}

Logger& Logger::Get()
{
    return logger;
}

void Logger::InitLogLevelColors()
{
    m_level_colors =
    {
        { LogLevel::NORMAL, BRIGHT_WHITE },
        { LogLevel::HINT, BRIGHT_GREEN },
        { LogLevel::WARNING, BRIGHT_YELLOW },
        { LogLevel::ERROR, BRIGHT_RED },
        { LogLevel::DEBUG, BRIGHT_BLUE }
    };
}

std::string_view Logger::LevelToStr( LogLevel level )
{
    switch( level )
        {
            case LogLevel::NORMAL:
                return "[Normal]";

            case LogLevel::HINT:
                return "[Hint]";

            case LogLevel::WARNING:
                return "[Warning]";

            case LogLevel::ERROR:
                return "[Error]";

            case LogLevel::DEBUG:
                return "[Debug]";

            default:
                return nullptr;
        }
}