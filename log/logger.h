#ifndef LOGGER
#define LOGGER
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ostream>
#include <chrono>
#include <filesystem>
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


#define LOGGING_ACTIVE
namespace fs = std::filesystem;
class Logger
{
private:
    inline static std::ofstream output;
    Logger();
public:
    typedef enum LOGGER_LEVEL {
        INFO,
        ERROR,
        ALL
    };
    static void initLogger();
    friend Logger operator<<(Logger l, const std::string& str);
    friend Logger operator<<(Logger l, const std::exception& err);
    friend Logger operator<<(Logger l, const char* str);
    friend Logger operator<<(Logger l, std::basic_ostream<char, std::char_traits<char>>& (*flusher)(std::basic_ostream<char, std::char_traits<char>>&));
    static Logger log;
};
#endif