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
#include <array>
#include <stb-master/stb_image.h>
class Mesh
{
private:
	VBO* vbo;
	EBO* ebo;
	std::reference_wrapper<VAO> vao;
	std::shared_ptr<Shader> shader;
	glm::mat4 model;
	void(*drawFunction)(Mesh*) = [](Mesh*) {};
public:
	Mesh(VBO*,
	EBO*, 
	std::reference_wrapper<VAO>,
	std::shared_ptr<Shader>);

	const glm::mat4& getModel();
    const VBO* getVBO();
    const EBO* getEBO();
	const std::shared_ptr<Shader> getShader();

	void transform(glm::mat4 transform);

	void setContext(void(*func)(Mesh* mesh));
	void draw();
};