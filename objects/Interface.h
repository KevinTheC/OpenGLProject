#include <stdlib.h>
#include <vector>
#include <algorithm>
#include "graphic_structures/Mesh.h"
#pragma once
//the struct is made up of 4 bounds that should be represented in a range of [0,1]
struct Area
{
    float top;
    float bottom;
    float left;
    float right;
    bool isInBounds(float x, float y)
    {
        return (x>=left&&x<=right)&&(y>=top&&y<=bottom);
    }
};
class Interface {
private:
    Mesh* mesh;
    std::vector<Area> keepAlive;
    std::vector<int> killKey;
public:
    Interface(Mesh* mesh, std::vector<Area> keepAlive, std::vector<int> killKey);
    std::string name;
    bool attemptKey(GLFWwindow* window, int key);
    bool attemptClick(GLFWwindow* window, float x, float y, int button);
    void draw() const;
    std::vector<Interface*> children;
};