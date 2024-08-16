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
#include "utils/Util.h"
#include <stdint.h>
#include "Shader.h"
#include <array>
#include <stb_image.h>
class Mesh
{
protected:
	VBO* vbo;
	EBO* ebo;
	VAO* vao;
	uint_fast8_t geometry;
	glm::mat4 model;
public:
	Mesh(VBO*,
	EBO*, 
	VAO*,
	std::shared_ptr<Shader>,
	uint_fast8_t);
	~Mesh();
	std::shared_ptr<Shader> shader;
	
	std::vector<Texture*> textures;
	const glm::mat4& getModel() const;
    VBO* getVBO() const;
    EBO* getEBO() const;
	std::shared_ptr<Shader> getShader() const;
	void scale(glm::vec3);
	void translate(glm::vec3);
	void rotate(GLfloat, glm::vec3);

	virtual void draw() const;
	std::string toString() const;
};