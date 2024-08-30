#pragma once
#include <utility>
#include <GL/glew.h>
#include <memory>
#include <vector>
#include "Shader.h"
class EBO
{
public:
	GLuint ID;
	EBO(std::vector<GLuint>&&);
	~EBO();

	EBO(const EBO& other)
		: indices(other.indices), ID(other.ID) {}
	EBO(EBO&& other) noexcept
		: indices(std::move(other.indices)), ID(std::exchange(other.ID,0)) {}
	EBO& operator=(const EBO& other)
	{
		return *this = EBO(other);
	}
	EBO& operator=(EBO&& other) noexcept
	{
		std::swap(indices, other.indices);
		std::swap(ID,other.ID);
		return *this;
	}

	void draw(int gl_geometry) const;
	void bind();
	void unbind();
	void erase();
	const std::vector<GLuint>& getValues() const;
private:
	std::vector<GLuint> indices;
};


