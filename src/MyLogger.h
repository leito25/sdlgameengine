//
// Created by lquinones on 6/1/26.
//
// Some popular loggers
// https://github.com/gabime/spdlog
// https://github.com/rxi/log.c

#ifndef SDLGAMEENGINE_MYLOGGER_H
#define SDLGAMEENGINE_MYLOGGER_H
#include <string>
#include <vector>

enum LogType
{
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
};

struct LogEntry
{
    int type;
    std::string message;
};

class MyLogger
{
    public:
    static std::vector<LogEntry> messages;// not just string but a logEntry struct
    static void Log(const std::string& message);
    static void Err(const std::string& message);
};


#endif //SDLGAMEENGINE_MYLOGGER_H
