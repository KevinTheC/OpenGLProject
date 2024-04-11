#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "VAO.h"
#include "EBO.h"
#include "Shader.h"
#include "objects/Renderable.h"
#include <array>
#include <stb-master/stb_image.h>
class Model
{
private:
	std::reference_wrapper<VBO> vbo;
	std::reference_wrapper<EBO> ebo;
	std::reference_wrapper<VAO> vao;
	Shader shader;
	glm::mat4 model;
	void(*drawFunction)() = []() {};
public:
	Model(std::reference_wrapper<VBO>,
	std::reference_wrapper<EBO>, 
	std::reference_wrapper<VAO>,
	Shader);

	const glm::mat4& getModel();
    const VBO& getVBO();
    const EBO& getEBO();
	const Shader& getShader();

	void transform(glm::mat4 transform);

	void setContext(void(*func)());
	void draw();
};