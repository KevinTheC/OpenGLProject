#pragma once
#include <stdlib.h>
#include "Mesh.h"
class Mesh2D : public Mesh
{
public:
    virtual void draw();
    Mesh2D(VBO&& vbo, EBO&& ebo, VAO&& vao, std::shared_ptr<Shader> shader, uint_fast8_t geometry) : 
    Mesh(std::move(vbo), std::move(ebo), std::move(vao), shader, geometry) {};
};