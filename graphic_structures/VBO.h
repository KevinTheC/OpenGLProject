#pragma once
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
	const std::vector<GLfloat>& getValues();
	void bind();
	void unbind();
	void erase();
	void update();
private:
	std::vector<GLfloat> vertices;
};

