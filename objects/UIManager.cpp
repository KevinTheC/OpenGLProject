#include "UIManager.h"
void UIManager::handleMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    double x;
    double y;
    glfwGetCursorPos(window,&x,&y);
    if (interfaces.size()>0)
        if (!interfaces.back()->attemptClick(window,(float)x,(float)y,button))
        {
            detachUI(interfaces.back());
        }
    
}
void UIManager::handleKey(GLFWwindow* window, Event e, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS)
        return;
    if (e == Escape && !interfaces.empty())
    {
        detachUI(interfaces.back());
        return;
    }
    else if (e == Escape)
    {
        registerUI(InterfaceFactory::defaultInterface());
    }
    if (!interfaces.empty())
        interfaces.back()->attemptKey(window, e);
}
void UIManager::registerUI(Interface* i)
{
    interfaces.push_back(i);
}
void UIManager::draw()
{
    for (const auto& val : interfaces)
        val->draw();
}
//calls for destruction of interface's children, then finds interface and destroys it
bool UIManager::detachUI(Interface* i)
{
    int index;
    for (index = 0; index < interfaces.size(); ++index)
    {
        if (interfaces[index] == i)
            break;
    }
    auto itr = index + interfaces.begin();
    if (itr == interfaces.end())
        return false;
    interfaces.erase(itr);
    delete(i);
    return true;
}
UIManager::UIManager()
{
    
};