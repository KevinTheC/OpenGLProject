#include "InterfaceFactory.h"
Interface* InterfaceFactory::defaultInterface()
{
    Interface* interface = new Interface(std::map<Mesh*,void(*)()>(), std::map<bool(*)(GLFWwindow*),void(*)()>());
    Mesh* mesh = FontTextureAtlas::buildText("HELLO",std::array<GLfloat,3>{0.0f,1.0f,0.0f});
    mesh->transparent = true;
    interface->drawables.push_back(mesh);
    mesh = InterfaceTextureAtlas::buildUI("./resources/textures/broThinkhePregnant.png");
    mesh -> scale(glm::vec3(0.5f,0.5f,0.0f));
    mesh -> translate(glm::vec3(1.0f,0.0f,0.0f));
    interface->drawables.push_back(mesh);
    return interface;
}