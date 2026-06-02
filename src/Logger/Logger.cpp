#include "Logger.h"

#include <chrono>
#include <ctime>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <sstream>

std::ofstream Logger::logFile;
std::mutex Logger::logMutex;
bool Logger::initialized = false;

bool Logger::Initialize(const std::string& filePath, bool append)
{
    std::lock_guard<std::mutex> lock(logMutex);

    if (initialized)
    {
        return true;
    }

    const std::filesystem::path path(filePath);
    const std::filesystem::path parentPath = path.parent_path();

    if (!parentPath.empty())
    {
        std::error_code error;
        std::filesystem::create_directories(parentPath, error);
        if (error)
        {
            std::cerr << "Logger directory error: " << error.message() << std::endl;
            return false;
        }
    }

    const std::ios::openmode mode = std::ios::out | (append ? std::ios::app : std::ios::trunc);
    logFile.open(filePath, mode);

    if (!logFile.is_open())
    {
        std::cerr << "Logger file error: could not open " << filePath << std::endl;
        return false;
    }

    initialized = true;
    logFile << "========== Log started " << CurrentTimestamp() << " ==========" << std::endl;
    return true;
}

void Logger::Shutdown()
{
    std::lock_guard<std::mutex> lock(logMutex);

    if (!initialized)
    {
        return;
    }

    logFile << "========== Log ended " << CurrentTimestamp() << " ==========" << std::endl;
    logFile.close();
    initialized = false;
}

bool Logger::IsInitialized()
{
    std::lock_guard<std::mutex> lock(logMutex);
    return initialized;
}

void Logger::Debug(const std::string& message)
{
    Write(LogLevel::Debug, message);
}

void Logger::Info(const std::string& message)
{
    Write(LogLevel::Info, message);
}

void Logger::Warning(const std::string& message)
{
    Write(LogLevel::Warning, message);
}

void Logger::Error(const std::string& message)
{
    Write(LogLevel::Error, message);
}

void Logger::Write(LogLevel level, const std::string& message)
{
    std::lock_guard<std::mutex> lock(logMutex);
    std::ostream& console = level == LogLevel::Error ? std::cerr : std::cout;

    if (!initialized)
    {
        console << "[" << LevelToString(level) << "] " << message << std::endl;
        return;
    }

    const std::string timestamp = CurrentTimestamp();
    const char* levelText = LevelToString(level);

    console << timestamp << " [" << levelText << "] " << message << std::endl;
    logFile << timestamp << " [" << levelText << "] " << message << std::endl;
}

const char* Logger::LevelToString(LogLevel level)
{
    switch (level)
    {
    case LogLevel::Debug:
        return "DEBUG";
    case LogLevel::Info:
        return "INFO";
    case LogLevel::Warning:
        return "WARNING";
    case LogLevel::Error:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}

std::string Logger::CurrentTimestamp()
{
    const auto now = std::chrono::system_clock::now();
    const std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    std::tm localTime{};
#if defined(_WIN32)
    localtime_s(&localTime, &currentTime);
#else
    localtime_r(&currentTime, &localTime);
#endif

    std::ostringstream timestamp;
    timestamp << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return timestamp.str();
}
