#ifndef LOGGER
#define LOGGER
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ostream>
#include <chrono>
#include <filesystem>
#define LOGGING_ACTIVE
namespace fs = std::filesystem;
class Logger
{
private:
    inline static std::ofstream output;
    Logger();
public:
    static void initLogger();
    friend Logger operator<<(Logger l, const std::string& str);
    friend Logger operator<<(Logger l, const std::exception& err);
    friend Logger operator<<(Logger l, const char* str);
    friend Logger operator<<(Logger l, std::basic_ostream<char, std::char_traits<char>>& (*flusher)(std::basic_ostream<char, std::char_traits<char>>&));
    static Logger log;
};
#endif