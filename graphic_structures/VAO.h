#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <unordered_map>
#include "VBO.h"
#include "Shader.h"
class VAO
{
public:
	static GLuint boundID;
	GLuint ID;
	void linkAttribs(std::shared_ptr<Shader> sh);
	void bind();
	void unbind();
	void erase();

	bool operator==(const VAO& other) const
	{
		return ID == other.ID;
	};
	static std::reference_wrapper<VAO> getVAO(std::shared_ptr<Shader> sh);
private:
	std::shared_ptr<Shader> shader;
	int attribs;
	int total;
	inline static std::unordered_map<int,VAO> vaomap;
	VAO(std::shared_ptr<Shader> sh);
};

template<>
struct std::hash<VAO>{
	std::size_t operator()(const VAO& v) const noexcept
    {
        return std::hash<GLuint>{}(v.ID);
    }
};
