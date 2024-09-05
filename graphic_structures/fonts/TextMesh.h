#pragma once
#include <stdlib.h>
#include "objects/Camera.h"
#include <stdint.h>
#include <array>
#include "graphic_structures/Mesh2D.h"
class TextMesh : public Mesh2D
{
public:
    void setColor(std::array<GLfloat, 3>);
    virtual void draw();
    TextMesh(VBO&& vbo, EBO&& ebo, VAO&& vao, std::shared_ptr<Shader> shader, uint_fast8_t geometry) : 
    Mesh2D(std::move(vbo), std::move(ebo), std::move(vao), shader, geometry) {};
private:
    std::array<GLfloat, 3> rgb;
};