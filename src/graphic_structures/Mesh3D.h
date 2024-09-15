#pragma once
#include <stdlib.h>
#include "Mesh.h"
#include "objects/Hitbox.h"
class Mesh3D : public Mesh{
public:
    virtual void draw();
    Mesh3D(VBO&& vbo, EBO&& ebo, VAO&& vao, std::shared_ptr<Shader> shader, uint_fast8_t geometry, Hitbox&& hb) : 
    Mesh(std::move(vbo), std::move(ebo), std::move(vao), shader, geometry), hb(std::move(hb)) {};
    const Hitbox& getHitbox();
    static bool intersect(Mesh3D&, Mesh3D&);
    static bool intersect(Mesh3D&, glm::vec3, glm::vec3);
private:
    Hitbox hb;
};