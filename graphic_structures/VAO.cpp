#include "graphic_structures/VAO.h"
VAO::VAO(std::shared_ptr<Shader> sh) {
	shader = sh;
	attribs = 0;
	total = 0;
	linkAttribs(sh);
	glGenVertexArrays(1, &ID);
	this->bind();
}
std::reference_wrapper<VAO> VAO::getVAO(std::shared_ptr<Shader> sh)
{
	if (vaomap.find(sh->ID)==vaomap.end())
	{
		VAO temp{sh};
		vaomap.emplace(sh->ID,temp);
	}
	return vaomap.find(sh->ID)->second;
}
//i put comment ontop of the shader like a boss so it knows the layout :glasses:
//in different APIs it might be better to have a single vao per format but opengl 3.3
void VAO::linkAttribs(std::shared_ptr<Shader> sh)
{
	attribs = 0;
	total = 0;
	std::vector<int> vec = sh->getAttribs();
	int offset = 0;
	//I have no idea whats going on here but I need to bind
	for (int i : vec)
		offset += i;
	for (int i : vec)
	{
		glVertexAttribPointer(attribs, i, GL_FLOAT, GL_FALSE, offset * sizeof(float), (void*)(total*sizeof(float)));
		glEnableVertexAttribArray(attribs++);
		total += i;
	}
	LOG_ALL(std::string("Attributes, then total: ")+std::to_string(attribs)+std::string(" ")+std::to_string(total));
}
void VAO::bind()
{
	glBindVertexArray(ID);
}
void VAO::unbind()
{
	glBindVertexArray(0);
}
void VAO::erase()
{
	glDeleteVertexArrays(1,&ID);
}