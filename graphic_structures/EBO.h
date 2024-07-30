#pragma once
#include <GL/glew.h>
#include <memory>
#include <vector>
#include "Shader.h"
class EBO
{
public:
	GLuint ID;
	EBO(std::vector<GLuint>* vec);
	~EBO();
	void draw(int gl_geometry);
	void bind();
	void unbind();
	void erase();
	std::vector<GLuint>& getValues();
private:
	std::vector<GLuint>* indices;
};


