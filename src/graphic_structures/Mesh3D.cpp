#include "Mesh3D.h"
void Mesh3D::draw()
{
    Mesh::draw();
}
const Hitbox& Mesh3D::getHitbox()
{
    return hb;
}
bool Mesh3D::intersect(Mesh3D& m1, Mesh3D& m2)
{
    return true;
}
bool Mesh3D::intersect(Mesh3D& m1, glm::vec3 rayOrigin, glm::vec3 rayDirection)
{
    return true;
}