#pragma once
#include <GL/glew.h>
#include <unordered_map>
#include <boost/functional/hash.hpp>
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

	const static std::reference_wrapper<VAO> getVAO(Shader& sh);
private:
	std::shared_ptr<Shader> shader;
	int attribs;
	int total;
	inline static std::unordered_map<int,VAO> vaomap;
	VAO(std::shared_ptr<Shader> sh);
};
typedef struct Vertex {
	glm::vec3 position;
	glm::vec2 UV;
} Vertex;
template<>
struct std::hash<Vertex>{
	std::size_t operator()(const Vertex& v) const noexcept
    {
        return std::hash<float>{}(v.position[0]) ^ 
		(std::hash<float>{}(v.position[1]) << 1) ^
		(std::hash<float>{}(v.position[2]) << 2) ^
		(std::hash<float>{}(v.UV[0]) << 3) ^
		(std::hash<float>{}(v.UV[1]) << 4);
    }
};
template<>
struct std::hash<glm::vec3>{
	std::size_t operator()(const glm::vec3& v) const noexcept
    {
        return std::hash<float>{}(v[0]) ^ 
		(std::hash<float>{}(v[1]) << 1) ^
		(std::hash<float>{}(v[2]) << 2);
    }
};
template<>
struct std::hash<glm::vec2>{
	std::size_t operator()(const glm::vec2& v) const noexcept
    {
        return std::hash<float>{}(v[0]) ^ 
		(std::hash<float>{}(v[1]) << 1);
    }
};