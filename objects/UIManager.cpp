#include "UIManager.h"
void UIManager::handleMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    double x;
    double y;
    glfwGetCursorPos(window,&x,&y);
    for (auto& val : interfaces)
        val.attemptClick(window,(float)x,(float)y,button);
}
void UIManager::handleKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    for (auto& val : interfaces)
        val.attemptKey(window, key);
}
void UIManager::registerUI(Interface& i)
{
    interfaces.push_back(i);
}
void UIManager::draw()
{
    for (auto& val : interfaces)
        val.draw();
}
UIManager::UIManager()
{
    
};