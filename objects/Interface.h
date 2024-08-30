#pragma once
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include "graphic_structures/Mesh.h"
#include "keybinds/Event.h"
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
    std::map<Mesh*,void(*)(Interface*)> regions;
    std::map<bool(*)(GLFWwindow*),void(*)()> keybinds;
public:
    std::vector<Mesh*> drawables;
    Interface(std::map<Mesh*,void(*)(Interface*)>, std::map<bool(*)(GLFWwindow*),void(*)()>);
    ~Interface();
    std::string name;
    bool attemptKey(GLFWwindow* window, Event event);
    bool attemptClick(GLFWwindow* window, float x, float y, int button);
    void draw() const;
    static Area bounds(GLFWwindow* window, Mesh* mesh);
};