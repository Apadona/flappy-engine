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
    { BLACK, std::to_string(static_cast<int>(BLACK)) + "m" },
    { RED, std::to_string(static_cast<int>(RED)) + "m" },
    { GREEN, std::to_string(static_cast<int>(GREEN)) + "m" },
    { YELLOW, std::to_string(static_cast<int>(YELLOW)) + "m" },
    { BLUE, std::to_string(static_cast<int>(BLUE)) + "m" },
    { MAGENTA, std::to_string(static_cast<int>(MAGENTA)) + "m" },
    { CYAN, std::to_string(static_cast<int>(CYAN)) + "m" },
    { WHITE, std::to_string(static_cast<int>(WHITE)) + "m" },

    { BRIGHT_BLACK, std::to_string(static_cast<int>(BRIGHT_BLACK)) + "m" },
    { BRIGHT_RED, std::to_string(static_cast<int>(BRIGHT_RED)) + "m" },
    { BRIGHT_GREEN, std::to_string(static_cast<int>(BRIGHT_GREEN)) + "m" },
    { BRIGHT_YELLOW, std::to_string(static_cast<int>(BRIGHT_YELLOW)) + "m" },
    { BRIGHT_BLUE, std::to_string(static_cast<int>(BRIGHT_BLUE)) + "m" },
    { BRIGHT_MAGENTA, std::to_string(static_cast<int>(BRIGHT_MAGENTA)) + "m" },
    { BRIGHT_CYAN, std::to_string(static_cast<int>(BRIGHT_CYAN)) + "m" },
    { BRIGHT_WHITE, std::to_string(static_cast<int>(BRIGHT_WHITE)) + "m" }
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
    {
        if( flags == LoggerFlags::DISABLE_ALL_FLAGS )
            m_flags &= 0;

        else
            m_flags |= static_cast<int>(flags);
    }

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

const char* Logger::LevelToStr( LogLevel level )
{
    switch( level )
        {
            case LogLevel::NORMAL:
                return "[Normal]";
            break;

            case LogLevel::HINT:
                return "[Hint]";
            break;

            case LogLevel::WARNING:
                return "[Warning]";
            break;

            case LogLevel::ERROR:
                return "[Error]";
            break;

            case LogLevel::DEBUG:
                return "[Debug]";
            break;
        }
}