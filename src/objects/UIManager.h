#pragma once
#include <stdlib.h>
#include "keybinds/Listeners.h"
#include <memory>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include "graphic_structures/mesh.h"
#include "graphic_structures/mesh_parsing/MeshParser.h"
#include "InterfaceFactory.h"
//UI manager should hold a reference to each mesh displayed, as well as an area on the screen where a click will destroy the menu.
//this can be done by holding a vector of areas, checking each area and then if the match is found 
class UIManager : public MouseButtonListener, public KeyListener{
public:
    static std::shared_ptr<UIManager> instance()
	{
		if (manager.get() == nullptr)
			manager = std::shared_ptr<UIManager>(new UIManager);
		return manager;
	}
	UIManager(UIManager const&) = delete;
	UIManager& operator=(UIManager const&) = delete;

    void handleKey(GLFWwindow* window, Event event, int scancode, int action, int mods);
    void handleMouseButton(GLFWwindow* window, int button, int action, int mods);
    void registerUI(Interface* i);
    bool detachUI(Interface* i);
    void draw();
private:
    std::vector<Interface*> interfaces;
    UIManager();
    inline static std::shared_ptr<UIManager> manager;
};