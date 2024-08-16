#include "Util.h"
std::vector<std::string> MyUtil::splitString(std::string str, char delimiter)
{
    std::vector<std::string> retvec;
    size_t slow = 0;
    size_t fast = 1;
    while (fast < str.length())
    {
        if (str[fast] == delimiter)
        {
            if (fast != slow)
                retvec.push_back(str.substr(slow, fast - slow));
            slow = ++fast;
        }
        else
            ++fast;
    }
    if (fast != slow)
        retvec.push_back(str.substr(slow, fast));
    return retvec;
};
std::string MyUtil::arrayifier(std::vector<std::string> strings, bool newlined)
{
    std::string str{"["};
    for (size_t i = 0; i < strings.size(); ++i)
    {
        if (i == strings.size()-1)
            str+=strings[i]+"]";
        else
            str+=(strings[i] + (newlined ? ",\n" : ", "));
    }
    return str;
}