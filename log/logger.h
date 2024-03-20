#ifndef LOGGER
#define LOGGER
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#define LOGGING true
namespace fs = std::filesystem;
class Logger
{
public:
    static void initLogger()
	{
        try {
        int highest = 0;
        for (const auto& entry : fs::directory_iterator("./log"))
        {
            std::string relative = entry.path().string();
            size_t idx = relative.find("log-");
            if (relative.find("log-")!=std::string::npos)
                highest = stoi(relative.substr(idx+4,relative.find(".")-(idx+4)));
        }
		output = std::ofstream(std::string("./log/log-").append(std::to_string(highest+1)).append(".log"),std::ios::out);
        output.flush();
        } catch (std::exception) {
            throw new std::runtime_error("Subfolder /log does not exist, can't instantiate logger.");
        }
	}
    friend Logger operator<<(Logger l,const std::string&);
    friend Logger operator<<(Logger l,const std::exception&);
    friend Logger operator<<(Logger l,const char*);
    static Logger log;
private:
    Logger();
    static std::ofstream output;
};
Logger operator<<(Logger l,const std::string& str)
{
    l << str.c_str();
    return l;
}
Logger operator<<(Logger l,const std::exception& err)
{
    l << err.what();
    return l;
}
Logger operator<<(Logger l, const char* str)
{
    if (!LOGGING)
        return l;
    if (!Logger::output.is_open())
        throw std::logic_error("Logger output stream is not initialized. Call initLogger() before attempting to write to the log.");
    Logger::output << str;
    return l;
    
}
#endif