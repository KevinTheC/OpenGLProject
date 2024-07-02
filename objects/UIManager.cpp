#include "UIManager.h"
void UIManager::handleMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    double x;
    double y;
    glfwGetCursorPos(window,&x,&y);
    for (const auto& val : interfaces)
        val.first->attemptClick(window,(float)x,(float)y,button);
}
void UIManager::handleKey(GLFWwindow* window, Event e, int scancode, int action, int mods)
{
    if (e == Escape && !interfaces.empty())
    {
        detachUI(interfaces.back().first);
        return;
    }
    else if (e == Test)
    {
        std::shared_ptr<Shader> sh(new Shader("./resources/shaders/texture.vert","./resources/shaders/texture.frag"));
        registerUI(new Interface(MeshParser::parseMesh("./resources/meshes/test.obj",sh),std::vector<Area>(),std::vector<Event>({Test2})));
    }
    interfaces.back().first->attemptKey(window, e);
}
void UIManager::registerUI(Interface* i)
{
    interfaces.push_back(std::pair<Interface*,bool>(i,true));
}
void UIManager::draw()
{
    for (const auto& val : interfaces)
        if (val.second)
            val.first->draw();
}
//calls for destruction of interface's children, then finds interface and destroys it
bool UIManager::detachUI(Interface* i)
{
    for (auto& val : i->children)
        detachUI(val);
    int index;
    for (index = 0; index < interfaces.size(); ++index)
    {
        if (interfaces[index].first == i)
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