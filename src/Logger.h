#pragma once

#include <fstream>
#include <mutex>
#include <string>

enum class LogLevel
{
    Debug,
    Info,
    Warning,
    Error
};

class Logger
{
public:
    static bool Initialize(const std::string& filePath = "logs/engine.log", bool append = false);
    static void Shutdown();
    static bool IsInitialized();

    static void Debug(const std::string& message);
    static void Info(const std::string& message);
    static void Warning(const std::string& message);
    static void Error(const std::string& message);
    static void Write(LogLevel level, const std::string& message);

private:
    static std::ofstream logFile;
    static std::mutex logMutex;
    static bool initialized;

    static const char* LevelToString(LogLevel level);
    static std::string CurrentTimestamp();
};
