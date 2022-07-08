#pragma once

#include <utils/logger.hpp>

extern Logger engine_logger;
extern Logger application_logger;

void InitializeLoggers();

//############### core logger ############### 
#define CORE_LOG_SOURCE(level) \
    engine_logger.Log(level,AppendStrings(__FILE__,__LINE__,__FUNCTION__))

#define CORE_LOG_ASSERT(condition,message) \
    if(!condition) \
    LOG_ERROR(message)

#define CORE_LOG_NORMAL(...) \
    engine_logger.Log(LogLevel::NORMAL,__VA_ARGS__)

#define CORE_LOG_HINT(...) \
    engine_logger.Log(LogLevel::HINT,__VA_ARGS__)

#define CORE_LOG_WARNING(...) \
    engine_logger.Log(LogLevel::WARNING,__VA_ARGS__)

#define CORE_LOG_ERROR(...) \
    engine_logger.Log(LogLevel::ERROR,__VA_ARGS__)

#define CORE_LOG_DEBUG(...) \
    engine_logger.Log(LogLevel::DEBUG,__VA_ARGS__)


//############### application logger ###############
#define LOG_SOURCE(level) \
    application_logger.Log(level,AppendStrings(__FILE__,__LINE__,__FUNCTION__))

#define LOG_ASSERT(condition,message) \
    if(!condition) \
    LOG_ERROR(message)

#define LOG_NORMAL(...) \
    application_logger.Log(LogLevel::NORMAL,__VA_ARGS__)

#define LOG_HINT(...) \
    application_logger.Log(LogLevel::HINT,__VA_ARGS__)

#define LOG_WARNING(...) \
    application_logger.Log(LogLevel::WARNING,__VA_ARGS__)

#define LOG_ERROR(...) \
    application_logger.Log(LogLevel::ERROR,__VA_ARGS__)

#define LOG_DEBUG(...) \
    application_logger.Log(LogLevel::DEBUG,__VA_ARGS__)