#pragma once
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ostream>
#include <chrono>
#include <filesystem>
#include <vector>
//DEFINE LOG LEVEL HERE

#define LOGGING_ALL
//_ALL, _DEBUG, _ALERT
//DEFINE LOG LEVEL HERE
#ifdef LOGGING_ALL
#define LOGGING_DEBUG
#define LOG_ALL(x) Logger::log << (x)
#endif

#ifdef LOGGING_DEBUG
#define LOG_DEBUG(x) Logger::log << (x)
#endif

#define LOG_ALERT(x) Logger::log << (x)

#ifndef LOGGING_ALL
#define LOG_ALL(x)
#endif
#ifndef LOGGING_DEBUG
#define LOG_DEBUG(x)
#endif


namespace fs = std::filesystem;
class Logger
{
private:
    inline static std::ofstream output;
    inline static std::vector<std::string> waiting;
    Logger();
public:
    static void queue(std::string);
    static std::string pop();
    typedef enum LOGGER_LEVEL {
        INFO,
        ERROR,
        ALL
    };
    static void initLogger();
    template <typename T>
    inline friend Logger operator<<(Logger l, T t)
    {
        if (!Logger::output.is_open())
            throw std::logic_error("Logger output stream is not initialized. Call initLogger() before attempting to write to the log.");
        const std::time_t var = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        Logger::output << std::put_time(std::localtime(&var), "[%F %T]") << " " << t << std::endl;
        return l;
    };
    friend Logger operator<<(Logger l, const char* str);
    friend Logger operator<<(Logger l, std::basic_ostream<char, std::char_traits<char>>& (*flusher)(std::basic_ostream<char, std::char_traits<char>>&));
    static Logger log;
};