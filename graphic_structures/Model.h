#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "graphic_structures/VAO.h"
#include "graphic_structures/EBO.h"
#include "graphic_structures/Shader.h"
#include "objects/Renderable.h"
#include <array>
#include <stb-master/stb_image.h>
class Model
{
private:
	VBO vbo;
	EBO ebo;
	VAO vao;
	Shader shader;
	glm::mat4 model;
	void(*drawFunction)() = []() {};
public:
	Model(std::string path, Shader sh);

	const glm::mat4& getModel();
    const VBO& getVBO();
    const EBO& getEBO();
	const Shader& getShader();

	void transform(glm::mat4 transform);

	void setContext(void(*func)());
	void draw();
};