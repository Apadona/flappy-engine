// exists only to initialize extern variable.

#include "core.hpp"

Logger engine_logger;
Logger application_logger;

void InitializeLoggers()
{
    engine_logger.SetSink(SinkType::CONSOLE,nullptr,nullptr);
    engine_logger.SetType(LogType::CORE);
    engine_logger.SetFlags(LoggerFlags::MENTION_LOG_LEVEL | LoggerFlags::MENTION_TYPE);

    application_logger.SetSink(SinkType::CONSOLE,nullptr,nullptr);
    application_logger.SetType(LogType::APPLICATION);
    application_logger.SetFlags(LoggerFlags::MENTION_LOG_LEVEL | LoggerFlags::MENTION_TYPE);
}