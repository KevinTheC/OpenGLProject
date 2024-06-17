#pragma once
#include "includes.h"
#include "Event.h"
class KeyListener {
public:
	virtual void handleKey(GLFWwindow* window, Event event, int scancode, int action, int mods) = 0;
};
class MouseButtonListener {
public:
	virtual void handleMouseButton(GLFWwindow* window, int button, int action, int mods) = 0;
};
class MouseWheelListener {
public:
	virtual void handleMouseWheel(GLFWwindow* window, double xoffset, double yoffset) = 0;
};
class DragListener {
public:
	virtual void handleDrag(GLFWwindow* window, double x, double y) = 0;
};
class ResizeListener {
public:
	virtual void handleResize(GLFWwindow* window, int w, int h) = 0;
};