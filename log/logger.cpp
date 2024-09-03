#include "log/logger.h"
Logger operator<<(Logger l,const char* str)
{
    if (!Logger::output.is_open())
        throw std::logic_error("Logger output stream is not initialized. Call initLogger() before attempting to write to the log.");
    const std::time_t var = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    Logger::output << std::put_time(std::localtime(&var), "[%F %T]") << " " << str << std::endl;
    return l;
}
Logger operator<<(Logger l, std::basic_ostream<char, std::char_traits<char>>& (*flusher)(std::basic_ostream<char, std::char_traits<char>>&))
{
    Logger::output << flusher;
}
void Logger::queue(std::string str)
{
    Logger::waiting.push_back(str);
    std::cout << Logger::waiting.size();
}
std::string Logger::pop()
{
    std::string total;
    while (!Logger::waiting.empty())
    {
        total = total + Logger::waiting.back();
        Logger::waiting.pop_back();
    }
    return total;
}

void Logger::initLogger()
{
    try
    {
        int highest = 0;
        for (const auto& entry : fs::directory_iterator("./logs"))
        {
            std::string relative = entry.path().string();
            size_t idx = relative.find("log-");
            if (relative.find("log-")!=std::string::npos)
            {
                int temp = stoi(relative.substr(idx+4,relative.find(".")-(idx+4)));
                    if (temp > highest)
                highest = temp;
            }
        }
	    output = std::ofstream(std::string("./logs/log-").append(std::to_string(highest+1)).append(".log"),std::ios::out);
        output.flush();
    }
    catch (std::exception&)
    {
        throw std::runtime_error("Subfolder /log does not exist, can't instantiate logger.");
    }
}
Logger::Logger()
{

}