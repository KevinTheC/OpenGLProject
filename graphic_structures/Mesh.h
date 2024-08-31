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
	VBO vbo;
	EBO ebo;
	VAO vao;
	uint_fast8_t geometry;
	glm::mat4 model;
	std::shared_ptr<Shader> shader;
public:
	bool orthographic;
	bool transparent;
	std::vector<Texture*> textures;

	Mesh(VBO&&,
	EBO&&, 
	VAO&&,
	std::shared_ptr<Shader>,
	uint_fast8_t);
	
	const glm::mat4& getModel() const;
    const VBO& getVBO() const;
    const EBO& getEBO() const;
	const VAO& getVAO() const;
	std::shared_ptr<Shader> getShader() const;
	void scale(glm::vec3);
	void translate(glm::vec3);
	void rotate(GLfloat, glm::vec3);
	virtual void draw();
	std::string toString() const;
};