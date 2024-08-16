#include "TextMesh.h"
void TextMesh::draw() const
{
    textures.at(0)->bind(0,GL_TEXTURE_2D);
    textures.at(0)->activate(shader.get(),0);
    GLuint rgbLoc = glGetUniformLocation(shader->ID, "rgb");
    glUniform3f(rgbLoc,rgb[0],rgb[1],rgb[2]);
    GLuint offsetLoc = glGetUniformLocation(shader->ID, "offest");
    glUniform3f(offsetLoc, offset[0], offset[1], offset[2]);
	vao->bind();
	ebo->draw(geometry);
	vao->unbind();
}
void TextMesh::setColor(std::array<GLfloat, 3> rgb)
{
    this->rgb = rgb;
}
void TextMesh::setOffset(std::array<GLfloat, 3> offset)
{
    this->offset = offset;
}