#include "graphic_structures/VAO.h"
VAO::VAO(std::shared_ptr<Shader> sh) {
	shader = sh;
	attribs = 0;
	total = 0;
	glGenVertexArrays(1, &ID);
}
//VBO MUST BE BOUND BEFORE DOING THIS!
void VAO::linkAttribs(std::shared_ptr<Shader> sh, VBO* vbo)
{
	bind();
	attribs = 0;
	total = 0;
	vbo->bind();
	std::vector<int> vec = sh->getAttribs();
	int stride = 0;
	//I have no idea whats going on here but I need to bind
	for (int i : vec)
		stride += i;
	for (int i : vec)
	{
		glVertexAttribPointer(attribs, i, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(total*sizeof(float)));
		glEnableVertexAttribArray(attribs++);

		total += i;
	}
	LOG_ALL(std::string("Attributes, then total: ")+std::to_string(attribs)+std::string(" ")+std::to_string(total));
	unbind();
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