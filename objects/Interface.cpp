#include "Interface.h"
Interface::Interface(Mesh* mesh, std::vector<Area> keepAlive, std::vector<Event> killKey)
{
    this->mesh = mesh;
    this->keepAlive = keepAlive;
    this->killKey = killKey;
}
bool Interface::attemptKey(GLFWwindow* window, Event event)
{
    if (std::count(killKey.begin(),killKey.end(),event)>0)
        return true;
    return false;
    //returning true/false with no actions is a placeholder
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
    for (const auto& child : children)
        child->draw();
    mesh->draw();
}