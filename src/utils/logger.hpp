#pragma once

#include <string>
#include <string_view>
#include <cstring>
#include <sstream>
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

enum class LoggerFlags : uint8_t
{
    DISABLE_ALL_FLAGS       = 0xFF,

    MENTION_LOG_LEVEL   = 1 << 0,
    MENTION_TYPE        = 1 << 1, // application or core.
    MENTION_TIME        = 1 << 2,
    MENTION_DATE        = 1 << 3,

    ALL_FLAGS           = MENTION_LOG_LEVEL | MENTION_TYPE | MENTION_TIME |
                          MENTION_DATE
};

struct LogLevelColor
{
    LogLevel level;
    Color color;
};

namespace
{
    template<typename T>
    inline std::string AppendStrings( const T value )
    {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }

    template<typename T, typename... Args>
    inline std::string AppendStrings( const T value, const Args ... args )
    {
        return AppendStrings(value) + ' ' +  AppendStrings(args...);
    }
}

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

        void SetFlags( LoggerFlags flags, bool set = true );
        bool HasFlags( LoggerFlags flags );

        template< typename First, typename ... Args >
        Logger& Log( LogLevel level, const First first, const Args ... args )
        {
            std::string message;
            bool has_info_builtin = false;

            if( HasFlags(LoggerFlags::MENTION_LOG_LEVEL) )
            {
                message += LevelToStr(level);
                has_info_builtin = true;
            }

            if( HasFlags(LoggerFlags::MENTION_TYPE) )
            {
                if( m_type == LogType::APPLICATION )
                    message += "[Application]";

                else
                    message += "[Core]";

                has_info_builtin = true;
            }

            if( has_info_builtin )
                message += ":";

            message += AppendStrings(first,args...);

            if( message.empty() )
                return *this;

            switch( m_place )
            {
                case SinkType::MEMORY:
                    std::strcat(m_out_memory,message.c_str());
                    std::strcat(m_out_memory,"\n");
                break;

                case SinkType::FILE:
                    m_out_file << message << std::endl;
                break;

                case SinkType::CONSOLE:
                    std::cout << m_escape_sequence_begin << m_color_codes[ m_level_colors[ static_cast<int>(level) ].color ]
                              << message << m_escape_sequence_end << std::endl;
                break;

                default:
                    std::cerr << "sink place not recognised!\n";
            }

            return *this;
        }

        static Logger& Get();

    private:
        void InitLogLevelColors();
        const char* LevelToStr( LogLevel level );

    private:
        SinkType m_place;
        LogType m_type;
        uint8_t m_flags;

        std::ofstream m_out_file; // output sink path in case of file outputting.
        char* m_out_memory; // output sink path in case of outputting to memory.

        std::vector<LogLevelColor> m_level_colors;

        static const std::string_view m_escape_sequence_begin;
        static const std::string_view m_escape_sequence_end;
        static std::map<Color,std::string> m_color_codes; // ansi string codes for each console color.

        static Logger logger;
};

#define LOG_SOURCE(level) \
    Logger::Get().Log(level,AppendStrings(__FILE__,__LINE__,__FUNCTION__))

#define LOG_ASSERT(condition,message) \
    if(!condition) \
    LOG_ERROR(message)

#define LOG_NORMAL(message) \
    Logger::Get().Log(LogLevel::NORMAL,message)

#define LOG_HINT(message) \
    Logger::Get().Log(LogLevel::HINT,message)

#define LOG_WARNING(message) \
    Logger::Get().Log(LogLevel::WARNING,message)

#define LOG_ERROR(message) \
    Logger::Get().Log(LogLevel::ERROR,message)

#define LOG_DEBUG(message) \
    Logger::Get().Log(LogLevel::DEBUG,message)
