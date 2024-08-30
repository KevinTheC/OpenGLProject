#pragma once
#include <stdlib.h>
#include "objects/Camera.h"
#include <stdint.h>
#include <array>
#include "graphic_structures/Mesh.h"
class TextMesh : public Mesh
{
public:
    void setColor(std::array<GLfloat, 3>);
    virtual void draw() const;
    TextMesh(VBO* vbo, EBO* ebo, VAO* vao, std::shared_ptr<Shader> shader, uint_fast8_t geometry) : 
    Mesh(vbo, ebo, vao, shader, geometry) {};
    virtual ~TextMesh();
private:
    std::array<GLfloat, 3> rgb;
};