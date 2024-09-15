#pragma once
#include <stdlib.h>
#include <vector>
#include <string>
#define maxfloat 999999.0f
#define minfloat -999999.0f
namespace MyUtil{
    std::vector<std::string> splitString(std::string, char);
    std::string arrayifier(std::vector<std::string>, bool);
}
