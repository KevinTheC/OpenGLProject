#pragma once
#include <utility>
#include "stdint.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "log/logger.h"
#include <vector>
#include <memory>
typedef struct Vertex {
	glm::vec3 position;
	glm::vec2 UV;
	GLfloat index;
	bool operator==(const Vertex& other) const
	{
		return position==other.position&&UV==other.UV;
	};
} Vertex;
template<>
struct std::hash<Vertex>{
	std::size_t operator()(const Vertex& v) const noexcept
    {
        return std::hash<float>{}(v.position[0]) ^ 
		(std::hash<float>{}(v.position[1]) << 1) ^
		(std::hash<float>{}(v.position[2]) << 2) ^
		(std::hash<float>{}(v.UV[0]) << 3) ^
		(std::hash<float>{}(v.UV[1]) << 4) ^
		(std::hash<float>{}(v.index) << 5);
    }
};
class VBO
{
public:
	GLuint ID;
	VBO(std::vector<GLfloat>&&);
	~VBO();

	VBO(const VBO& other)
		: ID(other.ID), vertices(other.vertices) {}
	VBO(VBO&& other) noexcept
		: vertices(std::move(other.vertices)), ID(std::exchange(other.ID,0)) {}
	VBO& operator=(const VBO& other)
	{
		return *this = VBO(other);
	}
	VBO& operator=(VBO&& other) noexcept
	{
		std::swap(vertices, other.vertices);
		ID = std::exchange(other.ID,0);
		return *this;
	}


	const std::vector<GLfloat>& getValues() const;
	void bind();
	void unbind();
	void erase();
	void update();
private:
	std::vector<GLfloat> vertices;
};

