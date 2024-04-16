#include "Mesh.h"
Mesh::Mesh(VBO* vbparam,
    EBO* ebparam, 
	VAO* vaparam,
    std::shared_ptr<Shader> shparam) : 
    vbo{vbparam}, ebo{ebparam}, vao{vaparam}, shader{shparam}
{
    model = glm::mat4(1.0f);
    shader->activate();
    vao->bind();
    vbo->bind();
    ebo->bind();
    vao->linkAttribs(shader,vbo);
    vao->unbind();
    vbo->unbind();
    ebo->unbind();
};
const glm::mat4& Mesh::getModel()
{
    return model;
}
const VBO* Mesh::getVBO()
{
    return vbo;
}
EBO* Mesh::getEBO()
{
    return ebo;
}
const std::shared_ptr<Shader> Mesh::getShader()
{
    return shader;
}
void Mesh::transform(glm::mat4 transform) {
    model += transform;
}
void Mesh::setContext(void(*func)(Mesh* mesh))
{
    drawFunction = func;
}
void Mesh::draw()
{
    drawFunction(this);
	int modelLoc = glGetUniformLocation(shader->ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    shader->activate();
	vao->bind();
	ebo->draw(geometry);
	vao->unbind();
}