#include "Mesh.h"
Mesh::Mesh(VBO* vbparam,
    EBO* ebparam, 
	std::reference_wrapper<VAO> vaparam,
    std::shared_ptr<Shader> shparam) : 
    vbo{vbparam}, ebo{ebparam}, vao{vaparam}, shader{shparam}
{
    model = glm::mat4(1.0f);
};
const glm::mat4& Mesh::getModel()
{
    return model;
}
const VBO* Mesh::getVBO()
{
    return vbo;
}
const EBO* Mesh::getEBO()
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
void Mesh::setContext(void(*func)())
{
    drawFunction = func;
}
void Mesh::draw()
{
    vbo->bind();
    drawFunction();
	int modelLoc = glGetUniformLocation(shader->ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	vao.get().bind();
	ebo->draw(shader);
	vao.get().bind();
}