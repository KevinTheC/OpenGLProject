#include "InterfaceFactory.h"
Interface* InterfaceFactory::defaultInterface()
{
    std::map<Mesh2D*,void(*)(Interface*)> map;
    Interface* interface = new Interface(map, std::map<bool(*)(GLFWwindow*),void(*)()>());
    Mesh2D* mesh = FontTextureAtlas::buildText("HELLO",std::array<GLfloat,3>{0.5f,0.5f,0.5f});
    //map.emplace(mesh,[](Interface* interface){});//UIManager::instance()->detachUI(interface);
    mesh->transparent = true;
    interface->drawables.push_back(mesh);
    mesh = InterfaceTextureAtlas::buildUI("./resources/textures/box.png");
    interface->drawables.push_back(mesh);
    return interface;
}