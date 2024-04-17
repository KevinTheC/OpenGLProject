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
#include "objects/Camera.h"
#include <stdint.h>
#include "Shader.h"
#include <array>
#include <stb-master/stb_image.h>
class Mesh
{
private:
	VBO* vbo;
	EBO* ebo;
	VAO* vao;

	std::shared_ptr<Shader> shader;
	uint_fast8_t geometry;
	glm::mat4 model;
	void(*drawFunction)(Mesh*) = [](Mesh*) {};
public:
	Mesh(VBO*,
	EBO*, 
	VAO*,
	std::shared_ptr<Shader>,
	uint_fast8_t);

	const glm::mat4& getModel();
    const VBO* getVBO();
    EBO* getEBO();
	const std::shared_ptr<Shader> getShader();
	void scale(glm::vec3);
	void translate(glm::vec3);
	void rotate(GLfloat, glm::vec3);

	void setContext(void(*func)(Mesh* mesh));
	void draw();
};