#include "UIManager.h"
void UIManager::handleMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    double x;
    double y;
    glfwGetCursorPos(window,&x,&y);
    for (auto& val : interfaces)
        val->attemptClick(window,(float)x,(float)y,button);
}
void UIManager::handleKey(GLFWwindow* window, Event e, int scancode, int action, int mods)
{
    if (e == Test)
    {
        LOG_ALL("Test");
    }
    for (const auto& val : interfaces)
    //this line is bugging
        val->attemptKey(window, e);
    LOG_ALL("Dispatched KeyEvent to interfaces");
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
    for (auto& val : i->children)
        detachUI(val);
    auto itr = std::find(interfaces.begin(),interfaces.end(),i);
    if (itr == interfaces.end())
        return false;
    interfaces.erase(itr);
    free(i);
}
UIManager::UIManager()
{
    
};