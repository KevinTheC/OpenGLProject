#include "Mesh2D.h"
void Mesh2D::draw()
{
    textures.at(0)->bind(0,GL_TEXTURE_2D);
    textures.at(0)->activate(shader,0);
    GLuint modelLoc = glGetUniformLocation(shader->ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	vao.bind();
	ebo.draw(geometry);
	vao.unbind();
}