#include "graphic_structures/VAO.h"
VAO::VAO(std::shared_ptr<Shader> sh) {
	shader = sh;
	attribs = 0;
	total = 0;
	glGenVertexArrays(1, &ID);
}
//VBO MUST BE BOUND BEFORE DOING THIS!
void VAO::linkAttribs(std::shared_ptr<Shader> sh, VBO& vbo, EBO& ebo)
{
	bind();
	vbo.bind();
	ebo.bind();
	attribs = 0;
	total = 0;

	std::vector<int> vec = sh->getAttribs();
	int stride = 0;
	for (int i : vec)
		stride += i;
	for (int i : vec)
	{
		glVertexAttribPointer(attribs, i, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(total*sizeof(float)));
		glEnableVertexAttribArray(attribs++);

		total += i;
	}
	LOG_ALL("Attributes, then total for VAO: "+std::to_string(attribs)+" "+std::to_string(total));
	vbo.unbind();
	unbind();
	ebo.unbind();
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
int VAO::getStride() const
{
	return total;
}
VAO::~VAO()
{
	if (glIsVertexArray(ID))
	    VAO::erase();
	LOG_ALL("VAO destroyed");
}