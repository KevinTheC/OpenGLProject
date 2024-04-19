#pragma once
#include <type_traits>
#include "includes.h"
#include <vector>
#include "keybinds/Listeners.h"
class InputController
{
private:
	static std::vector<DragListener*> draggers;
	static std::vector<ResizeListener*> resizers;
	static std::vector<MouseButtonListener*> mbListeners;
	static std::vector<MouseWheelListener*> mwListeners;
	static std::vector<KeyListener*> kListeners;
	template <typename T>
	static void remove(T* t, std::vector<T*> vec) {
		for (int i = 0; i < vec.size(); i++)
			if (t == vec.at(i))
			{
				vec.erase(vec.begin() + i);
				return;
			}
	}
public:
	template <typename T>
	static void addObserver(T* t) {
		if constexpr (std::is_base_of<DragListener,T>::value)
			draggers.push_back(t);
		if constexpr (std::is_base_of<ResizeListener,T>::value)
			resizers.push_back(t);
		if constexpr (std::is_base_of<MouseButtonListener,T>::value)
			mbListeners.push_back(t);
		if constexpr (std::is_base_of<KeyListener,T>::value)
			kListeners.push_back(t);
		if constexpr (std::is_base_of<MouseWheelListener,T>::value)
			mwListeners.push_back(t);
	}
	template <typename T>
	static void removeObserver(T* t) {
		if constexpr (std::is_base_of<DragListener,T>::value)
			remove(t, draggers);
		if constexpr (std::is_base_of<ResizeListener,T>::value)
			remove(t, resizers);
		if constexpr (std::is_base_of<MouseButtonListener,T>::value)
			remove(t, mbListeners);
		if constexpr (std::is_base_of<KeyListener,T>::value)
			remove(t, kListeners);
		if constexpr (std::is_base_of<MouseWheelListener,T>::value)
			remove(t, mwListeners);
	}


	static void GLFWmouseMoveCB(GLFWwindow* window, double xnewpos, double ynewpos)
	{
		for (DragListener* dl : draggers)
			dl->handleDrag(window, xnewpos, ynewpos);
	}
	static void GLFWresizeCB(GLFWwindow* window, int w, int h)
	{
		for (ResizeListener* rl : resizers)
			rl->handleResize(window, w, h);
	}
	static void GLFWmouseButtonCB(GLFWwindow* window, int button, int action, int mods)
	{
		for (MouseButtonListener* mbl : mbListeners)
			mbl->handleMouseButton(window, button, action, mods);
	}
	static void GLFWkeyCB(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		for (KeyListener* kl : kListeners)
			kl->handleKey(window,key,scancode,action,mods);
	}
	static void GLFWmouseWheelCB(GLFWwindow* window, double xoffset, double yoffset)
	{
		for (MouseWheelListener* mw : mwListeners)
			mw->handleMouseWheel(window, xoffset, yoffset);
	}
};
std::vector<DragListener*> InputController::draggers;
std::vector<ResizeListener*> InputController::resizers;
std::vector<MouseButtonListener*> InputController::mbListeners;
std::vector<MouseWheelListener*> InputController::mwListeners;
std::vector<KeyListener*> InputController::kListeners;