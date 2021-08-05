#pragma once

#include <string>
#include <string_view>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>

enum class SinkType
{
    MEMORY,
    FILE,
    CONSOLE
};

enum class LogType
{
    CORE,
    APPLICATION
};

#ifdef ERROR
    #undef ERROR
#endif

enum class LogLevel
{
    NORMAL,
    HINT,
    WARNING,
    ERROR,
    DEBUG
};

// all the console colors that an ANSI compatible console supports.
enum Color
{
    BLACK               = 30,
    RED                 = 31,
    GREEN               = 32,
    YELLOW              = 33,
    BLUE                = 34,
    MAGENTA             = 35,
    CYAN                = 36,
    WHITE               = 37,

    BRIGHT_BLACK        = 90,
    BRIGHT_RED          = 91,
    BRIGHT_GREEN        = 92,
    BRIGHT_YELLOW       = 93,
    BRIGHT_BLUE         = 94,
    BRIGHT_MAGENTA      = 95,
    BRIGHT_CYAN         = 96,
    BRIGHT_WHITE        = 97
};

struct LogLevelColor
{
    LogLevel level;
    Color color;
};

// quick and dirty abstraction for ascii color printing to consoles.
class Logger
{
    public:
        // it must be called before any object of this class is made (specially on windows).
        static bool Init();

        Logger();
        Logger( SinkType sink, LogType = LogType::APPLICATION, char* dump_memory = nullptr,
                char* dump_file = nullptr );

        ~Logger();

        void SetSink( SinkType _type, char* dump_memory, char* dump_file );
        void SetType( LogType _type );
        void SetLogLevelColor( LogLevel level, Color color );

        void Log( const std::string& log , LogLevel = LogLevel::NORMAL );
        //template<typename T, typename ... args>
        //void Log( T arg1, args ... other, LogLevel = LogLevel::NORMAL );

        static Logger& Get();

    private:
        void InitLogLevelColors();
        const char* LevelToStr( LogLevel level );

    private:
        SinkType m_place;
        LogType m_type;

        std::ofstream m_out_file; // output sink path in case of file outputting.
        char* m_out_memory; // output sink path in case of outputting to memory.

        std::vector<LogLevelColor> m_level_colors;

        static const std::string_view m_escape_sequence_begin;
        static const std::string_view m_escape_sequence_end;
        static std::map<Color,std::string> m_color_codes; // ansi string codes for each console color.

        static Logger logger;
};

#define LOG_ASSERT(condition,message) \
    if(!condition) \
    LOG_ERROR(message)

#define LOG_NORMAL(message) \
    Logger::Get().Log(message,LogLevel::NORMAL)

#define LOG_HINT(message) \
    Logger::Get().Log(message,LogLevel::HINT)

#define LOG_WARNING(message) \
    Logger::Get().Log(message,LogLevel::WARNING)

#define LOG_ERROR(message) \
    Logger::Get().Log(message,LogLevel::ERROR)

#define LOG_DEBUG(message) \
    Logger::Get().Log(message,LogLevel::DEBUG)
