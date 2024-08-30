#pragma once
#include <utility>
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
	void linkAttribs(std::shared_ptr<Shader> sh, VBO& vbo, EBO& ebo);
	void bind();
	void unbind();
	void erase();
	int getStride() const;

	VAO(std::shared_ptr<Shader> sh);
	VAO(const VAO& other)
		: ID(other.ID), shader(other.shader) {}
	VAO(VAO&& other) noexcept
		: ID(std::exchange(other.ID,0)), shader(std::exchange(other.shader,nullptr)) {}
	VAO& operator=(const VAO& other)
	{
		return *this = VAO(other);
	}
	VAO& operator=(VAO&& other) noexcept
	{
		std::swap(shader, other.shader);
		std::swap(ID,other.ID);
		return *this;
	}
	~VAO();
private:
	std::shared_ptr<Shader> shader;
	int attribs;
	int total;
};
