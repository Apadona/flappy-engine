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

#include "helpers.hpp"
#include "time.hpp"

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

// WINAPI also defines this.
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
    DISABLE_ALL_FLAGS       = 0x00,

    MENTION_LOG_LEVEL       = 1 << 1,
    MENTION_TYPE            = 1 << 2, // application or core.
    MENTION_DATE            = 1 << 3, // not yet implemented.
    MENTION_TIME            = 1 << 4, // not yet implemented.

    ALL_FLAGS               = MENTION_LOG_LEVEL | MENTION_TYPE | MENTION_TIME |
                              MENTION_DATE
};

inline LoggerFlags operator|( LoggerFlags first, LoggerFlags second )
{
    return static_cast<LoggerFlags>(AsInteger(first) | AsInteger(second));
}

inline LoggerFlags operator&( LoggerFlags first, LoggerFlags second )
{
    return static_cast<LoggerFlags>(AsInteger(first) & AsInteger(second));
}

inline LoggerFlags operator|=( LoggerFlags& first, LoggerFlags second )
{
    first = first | second;
    return first;
}

inline LoggerFlags operator&=( LoggerFlags& first, LoggerFlags second )
{
    first = first & second;
    return first;
}

inline LoggerFlags operator~( LoggerFlags value )
{
    return static_cast<LoggerFlags>( ~(static_cast<uint8_t>(value)) );
}

struct LogLevelColor
{
    LogLevel level;
    Color color;
};

namespace
{
    template<typename T>
    inline std::string AppendStrings( T&& value )
    {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }

    template<typename T, typename... Args>
    inline std::string AppendStrings( T&& value, Args&& ... args )
    {
        return AppendStrings(std::forward<T>(value)) + AppendStrings(std::forward<Args>(args)...);
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
        Logger& Log( LogLevel level, First&& first, Args&& ... args )
        {
            std::string message; // to be outputted.
            bool has_info_built_in = false;
            
            if( HasFlags(LoggerFlags::MENTION_LOG_LEVEL) )
            {
                message += LevelToStr(level);
                has_info_built_in = true;
            }

            if( HasFlags(LoggerFlags::MENTION_TYPE) )
            {
                if( m_type == LogType::APPLICATION )
                    message += "[Application]";

                else
                    message += "[Core]";

                has_info_built_in = true;
            }
/*
            Time now;
            if( HasFlags(LoggerFlags::MENTION_DATE) )
            {
                message += now.date_time.ToString();

                has_info_built_in = true;
            }

            if( HasFlags(LoggerFlags::MENTION_TIME) )
            {
                message += now.day_time.ToString();

                has_info_built_in = true;
            }
*/
            if( has_info_built_in )
                message += ":";

            message += AppendStrings(std::forward<First>(first),std::forward<Args>(args)...);

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

    private:
        void InitLogLevelColors();
        std::string_view LevelToStr( LogLevel level );

    private:
        SinkType m_place;
        LogType m_type;
        LoggerFlags m_flags;

        std::ofstream m_out_file; // output sink path in case of file outputting.
        char* m_out_memory; // output sink path in case of outputting to memory.

        std::vector<LogLevelColor> m_level_colors; // or std::map<LogLevel,Color>?

        static const std::string_view m_escape_sequence_begin;
        static const std::string_view m_escape_sequence_end;
        static std::map<Color,std::string> m_color_codes; // ansi string codes for each console color.
};
