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
#include "Texture.h"
#include "EBO.h"
#include "objects/Camera.h"
#include <stdint.h>
#include "Shader.h"
#include <array>
#include <stb_image.h>
class Mesh
{
private:
	VBO* vbo;
	EBO* ebo;
	VAO* vao;
	uint_fast8_t geometry;
	glm::mat4 model;
	void(*drawFunction)(const Mesh*) = [](const Mesh*) {};
public:
	Mesh(VBO*,
	EBO*, 
	VAO*,
	std::shared_ptr<Shader>,
	uint_fast8_t);
	std::shared_ptr<Shader> shader;
	
	std::vector<Texture*> textures;
	const glm::mat4& getModel();
    const VBO* getVBO();
    EBO* getEBO();
	const std::shared_ptr<Shader> getShader();
	void scale(glm::vec3);
	void translate(glm::vec3);
	void rotate(GLfloat, glm::vec3);

	void setContext(void(*func)(const Mesh* mesh));
	void draw() const;
};