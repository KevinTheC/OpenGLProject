#include "InputController.h"
InputController::InputController()
{
    if (!loadCustom())
        loadDefault();
}
bool InputController::loadCustom()
{
    std::ifstream stream{"./resources/keybinds"};
    if (!stream.good())
        return false;
    while (!stream.eof())
    {
        std::string str;
        std::getline(stream,str);
        std::vector<std::string> vec = MyUtil::splitString(str,' ');
        try {
            int i = std::stoi(vec[0]);
            bindingMap.emplace(i,(Event)std::stoi(vec[1]));
        } catch (...) {
            return false;
        }
    }
    bindingMap.emplace(GLFW_KEY_ESCAPE, Escape);
    return true;
}
//USING A KEY NOT BOUND IS THE PROBLEM
void InputController::loadDefault()
{
    bindingMap.clear();
    bindingMap.emplace(GLFW_KEY_EQUAL, Zoom);
    bindingMap.emplace(GLFW_KEY_LEFT_CONTROL, Pan);
    bindingMap.emplace(GLFW_KEY_LEFT_ALT, Rotate);
    bindingMap.emplace(GLFW_KEY_9, Test);
    bindingMap.emplace(GLFW_KEY_ESCAPE, Escape);
}
void InputController::writeBinds()
{
    std::ofstream str{"./resources/keybinds",std::ios::out};
    for (auto const& pair : bindingMap)
    {
        str << pair.first << " " << pair.second << "\n";
    }
    str.flush();
}
void InputController::bind(const int key,Event e)
{
    for (auto const& pair : bindingMap)
    {
        if (pair.second == e)
        {
            bindingMap.erase(bindingMap.find(pair.first));
            bindingMap.emplace(key,e);
            return;
        }
    }
}
int InputController::getKey(GLFWwindow* window, Event e)
{
    for (auto const& pair : bindingMap)
    {
        if (pair.second == e)
        {
            return glfwGetKey(window,pair.first);
        }
    }
    return -1;
}
Event InputController::getBinding(int glfwkey)
{
    if (bindingMap.find(glfwkey)==bindingMap.end())
        return Unbound;
    return bindingMap.at(glfwkey);
}