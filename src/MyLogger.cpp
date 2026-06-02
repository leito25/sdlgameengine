//
// Created by lquinones on 6/1/26.
//

#include "MyLogger.h"
#include <iostream>
#include <chrono>
#include <format>

std::vector<LogEntry> MyLogger::messages;// This should be declared because is a static

std::string CurrentDateTimeToString()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string output(30, '\0');
    std::strftime(&output[0], output.size(), "%d-%b-%Y %H:%M:%S", std::localtime(&now));
    return output;
}

void MyLogger::Log(const std::string& message)
{
    // TODO: Print on the console the message
    // Use a special format
    // LOG: [ 12/Oct/2020 09:12:17] - Here goes the message
    // This should be displayed in green
    //Getting the current time
    //std::string output = "LOG: [" + CurrentDateTimeToString() + "] " + message;
    //std::cout << "\x1B[32m" << output << "\033[0m" << std::endl;

    // Now using the LogEntry struct
    LogEntry logEntry;
    logEntry.type = LOG_INFO;
    logEntry.message = "LOG: [" + CurrentDateTimeToString() + "] " + message;
    std::cout << "\x1B[32m" << logEntry.message << "\033[0m" << std::endl;
    messages.push_back(logEntry);
}

void MyLogger::Err(const std::string& message)
{
    // TODO: Print on the console the message
    // Use a special format
    // LOG: [ 12/Oct/2020 09:12:17] - Here goes the message
    // This should be displayed in red
    //std::string output = "ERR: [" + CurrentDateTimeToString() + "] " + message;
    //std::cout << "\x1B[91m" << output << "\033[0m" << std::endl;

    // Now using the LogEntry struct
    LogEntry logEntry;
    logEntry.type = LOG_ERROR;
    logEntry.message = "LOG: [" + CurrentDateTimeToString() + "] " + message;
    std::cout << "\x1B[32m" << logEntry.message << "\033[0m" << std::endl;
    messages.push_back(logEntry);
}
