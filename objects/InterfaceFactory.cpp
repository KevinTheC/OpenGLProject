#include "InterfaceFactory.h"
Interface* InterfaceFactory::defaultInterface()
{
    std::map<Mesh*,void(*)(Interface*)> map;
    Interface* interface = new Interface(map, std::map<bool(*)(GLFWwindow*),void(*)()>());
    Mesh* mesh = FontTextureAtlas::buildText("HELLO",std::array<GLfloat,3>{0.0f,1.0f,0.0f});
    //map.emplace(mesh,[](Interface* interface){});//UIManager::instance()->detachUI(interface);
    mesh->transparent = true;
    interface->drawables.push_back(mesh);
    mesh = InterfaceTextureAtlas::buildUI("./resources/textures/broThinkhePregnant.png");
    interface->drawables.push_back(mesh);
    for (Mesh* m : interface->drawables)
    {
        m -> scale(glm::vec3(0.5f,0.5f,0.0f));
        m -> translate(glm::vec3(1.0f,0.0f,0.0f));
    }
    return interface;
}