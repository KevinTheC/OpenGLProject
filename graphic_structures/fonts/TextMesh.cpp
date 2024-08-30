#include "TextMesh.h"
void TextMesh::draw() const
{
    textures.at(0)->bind(0,GL_TEXTURE_2D);
    textures.at(0)->activate(shader.get(),0);
    GLuint rgbLoc = glGetUniformLocation(shader->ID, "rgb");
    glUniform3f(rgbLoc,rgb[0],rgb[1],rgb[2]);
    GLuint modelLoc = glGetUniformLocation(shader->ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	vao->bind();
	ebo->draw(geometry);
	vao->unbind();
}
TextMesh::~TextMesh()
{	
    LOG_ALL("Began TextMesh::~TextMesh() at " + Logger::toString((intptr_t)this));
}
void TextMesh::setColor(std::array<GLfloat, 3> rgb)
{
    this->rgb = rgb;
}