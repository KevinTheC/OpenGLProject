#include "EBO.h"
EBO::EBO(std::vector<GLuint>&& vec)
{
	indices = std::move(vec);
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
EBO::~EBO()
{
	unbind();
	// delete(indices);
	LOG_ALL("Deleted an EBO");
}
void EBO::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}
void EBO::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void EBO::erase()
{
	glDeleteBuffers(1, &ID);
}
void EBO::draw(int gl_geometry)
{
	glDrawElements(gl_geometry, indices.size(), GL_UNSIGNED_INT, (void*)0);
}
std::vector<GLuint>& EBO::getValues()
{
	return indices;
}