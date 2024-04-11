#pragma once
#include <GL/glew.h>
#include <memory>
#include <vector>
#include "Shader.h"
class EBO
{
public:
	GLuint ID;
	EBO(std::shared_ptr<std::vector<GLuint>> vec);
	void draw(Shader* sh);
	void bind();
	void unbind();
	void erase();
private:
	std::shared_ptr<std::vector<GLuint>> indices;
};


