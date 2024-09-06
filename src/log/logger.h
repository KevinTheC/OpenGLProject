#pragma once
#include <stdlib.h>
#include <type_traits>
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

// How the struct works is that the method "test"'s version with the integer as a parameter only exists if the method can compile. If the method can't compile, the varargs version
// of the method isn't overloaded, and therefore passing an int as the parameter calls the catch-all version that returns false. We have to use this roundabout way of things because
// std::to_string is overloaded, and decltype(std::to_string(std::declval<U>())) won't compile. The second expression of the lambda (or whatever this syntax is called) is what
// is actually returned from this.
template <typename T>
struct is_to_string_invocable {
    private:
        template <typename U>
        static auto test(int) -> decltype(std::to_string(std::declval<U>()), std::true_type());
        
        template <typename>
        static std::false_type test(...);
    public:
        static constexpr bool value = decltype(test<T>(0))::value;
};
template <typename T>
struct has_toString {
    private:
        template <typename U>
        static auto test(int) -> decltype(&U::toString, std::true_type());
    
        template <typename>
        static std::false_type test(...);
    public:
        static constexpr bool value = decltype(test<T>(0))::value;
};


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
    enum LOGGER_LEVEL {
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
    // I wanted a way to easily do a catch-all function for converting everything I wanted to possibly log into string form so it could be passed into the logger. In order to do this
// I needed to consider types that can be used to create std::string directly, types that could be already converted by existing logic by std::to_string, and my own custom 
// implementations. The path I took was to create three templated functions based on the principle of SFINAE (Substitution Failure Is Not An Error).
// A struct is used to evaluate whether std::to_string or std::string constructor works with the given argument, which should have no overlap. This struct is used to supply a value
// to std::enable_if.
    template <typename T>
    static typename std::enable_if<is_to_string_invocable<T>::value, std::string>::type toString(const T& value);
    template <typename T>
    static typename std::enable_if<std::is_constructible<std::string,T>::value, std::string>::type toString(const T& value);
    template <typename T>
    static typename std::enable_if<has_toString<T>::value, std::string>::type toString(const T& value);
};



template <typename T>
typename std::enable_if<is_to_string_invocable<T>::value, std::string>::type
Logger::toString(const T& value)
{
    return std::to_string(value);
};
template <typename T>
typename std::enable_if<std::is_constructible<std::string,T>::value, std::string>::type 
Logger::toString(const T& value)
{
    return std::string(value);
}
template <typename T>
typename std::enable_if<has_toString<T>::value, std::string>::type 
Logger::toString(const T& value)
{
    return value.toString();
}