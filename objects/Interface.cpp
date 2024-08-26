#include "Interface.h"
Interface::Interface(std::vector<Area> keepAlive, std::vector<Event> killKey)
{
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
    for (auto const& val : drawables)
        val->draw();
}
Interface::~Interface()
{
    for (auto const& val : drawables)
        delete(val);
}