#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <unordered_map>
#include "VBO.h"
#include "EBO.h"
#include "Shader.h"
class VAO
{
public:
	static GLuint boundID;
	GLuint ID;
	void linkAttribs(std::shared_ptr<Shader> sh, VBO* vbo, EBO* ebo);
	void bind();
	void unbind();
	void erase();
	int getStride();
	VAO(std::shared_ptr<Shader> sh);
	~VAO();
private:
	std::shared_ptr<Shader> shader;
	int attribs;
	int total;
};
