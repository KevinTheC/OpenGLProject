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
	void draw(std::shared_ptr<Shader> sh);
	void bind();
	void unbind();
	void erase();
	const std::vector<GLuint>& getValues();
private:
	std::vector<GLuint>* indices;
};


