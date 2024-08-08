#include "TextMesh.h"
void TextMesh::setContext() const
{
    GLuint rgbLoc = glGetUniformLocation(shader->ID, "rgb");
    glUniform3f(rgbLoc,rgb[0],rgb[1],rgb[2]);
}
void TextMesh::setColor(std::array<GLfloat, 3> rgb)
{
    this->rgb = rgb;
}