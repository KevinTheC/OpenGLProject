#include "InterfaceFactory.h"
Interface* InterfaceFactory::defaultInterface()
{
    Interface* interface = new Interface(std::vector<Area>(), std::vector<Event>());
    Mesh* mesh = FontTextureAtlas::buildText("HELLO",std::array<GLfloat,3>{0.0f,1.0f,0.0f});
    mesh->transparent = true;
    interface->drawables.push_back(mesh);
    interface->drawables.push_back(InterfaceTextureAtlas::buildUI("./resources/textures/broThinkhePregnant.png"));
    return interface;
}