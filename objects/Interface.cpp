#include "Interface.h"
Interface::Interface(Mesh* mesh, std::vector<Area> keepAlive, std::vector<int> killKey)
{
    mesh = mesh;
    keepAlive = keepAlive;
    killKey = killKey;
}
bool Interface::attemptKey(GLFWwindow* window, Event event)
{
    if (std::count(killKey.begin(),killKey.end(),event)>0)
        return true;
}
bool Interface::attemptClick(GLFWwindow* window, float x, float y, int button)
{
    for (auto& val : keepAlive)
        if (!val.isInBounds(x,y))
            return true;
    return false;
}
void Interface::draw() const
{
    //for (const auto& child : children)
    //    child->draw();
    mesh->draw();
}