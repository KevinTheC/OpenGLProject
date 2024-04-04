#pragma once
#ifndef VAO_CLASS_H
#define VAO_CLASS_H
#include <GL/glew.h>
#include <unordered_map>
#include "VBO.h"
#include "Shader.h"
class VAO
{
public:
	static GLuint boundID;
	GLuint ID;
	void linkAttribs(Shader& sh);
	void bind();
	void unbind();
	void erase();

	const static VAO& getVAO(Shader& sh);
private:
	std::shared_ptr<Shader> shader;
	int attribs;
	int total;
	inline static std::unordered_map<int,VAO> vaomap;
	VAO(std::shared_ptr<Shader> sh);
};
#endif
