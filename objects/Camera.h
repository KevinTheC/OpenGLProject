#ifndef CAMERA_H
#define CAMERA_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "OpenGLIncludes.h"
#include <array>
#include <cmath>
#include "objects/Object.h"
#include "objects/CubeFactory.h"
#include "keybinds/listeners.h"
#define PI 3.1416f
#define screensize 3.0971f
#define MAX_FLOAT 3.4028235E38f
#define FOV 90.0f
#define displayc(sargs, args) std::cout << sargs << args << "\n"
#define PAN_SCALAR .005f
class Camera : public DragListener, public MouseButtonListener, public ResizeListener, public MouseWheelListener, public KeyListener
{
public:
	static std::shared_ptr<Camera> instance()
	{
		if (camera.get() == nullptr)
			camera = std::shared_ptr<Camera>(new Camera);
		return camera;
	}
	Camera(Camera const&) = delete;
	Camera& operator=(Camera const&) = delete;

	void linkShader(Shader* sh);
	void updateProjection(int w, int h);
	void setFocus(glm::mat4 focus);
	const glm::mat4& getProj();
	const glm::mat4& getView();
	

	void handleMouseWheel(GLFWwindow* window, double xoffset, double yoffset);
	void handleMouseButton(GLFWwindow* window, int button, int action, int mods);
	void handleDrag(GLFWwindow* window, double xnewpos, double ynewpos);
	void handleResize(GLFWwindow* window, int width, int height);
	void handleKey(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
	Camera();
	glm::vec3 panDirection(float xdiff, float ydiff);
	float subtractFromOne(float);
	glm::mat4 proj;
	glm::mat4 view;
	glm::vec3 center;
	glm::vec3 viewpoint;
	glm::vec2 toXY(glm::mat4 model, glm::vec4 point);
	static float distance(std::pair<float,float>&, std::pair<float,float>);
	Object::VertIterator getClosestTo(std::pair<float,float> pos,Object& o);
	static std::shared_ptr<Camera> camera;

	void notify(glm::mat4 location);
	void refresh();

	int width;
	int height;
	glm::mat4 focus;
	unsigned int uboMatrices;
	float total;
	float roll;
	float yaw;
	double xpos;
	double ypos;
};
#endif
