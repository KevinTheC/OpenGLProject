#include "UIManager.h"
void UIManager::handleMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    double x;
    double y;
    glfwGetCursorPos(window,&x,&y);
    if (interfaces.size()>0)
        interfaces.back()->attemptClick(window,(float)x,(float)y,button);
}
void UIManager::handleKey(GLFWwindow* window, Event e, int scancode, int action, int mods)
{
    if (e == Escape && !interfaces.empty())
    {
        detachUI(interfaces.back());
        return;
    }
    else if (e == Test)
    {
        // std::shared_ptr<Shader> sh(new Shader("./resources/shaders/texture.vert","./resources/shaders/texture.frag"));
        // registerUI(new Interface(MeshParser::parseMesh("./resources/meshes/test.obj",sh),std::vector<Area>(),std::vector<Event>({Test2})));
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
    free(i);
    return true;
}
UIManager::UIManager()
{
    
};