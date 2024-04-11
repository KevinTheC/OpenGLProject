#include "Model.h"
Model::Model(std::reference_wrapper<VBO> vbparam,
    std::reference_wrapper<EBO> ebparam, 
	std::reference_wrapper<VAO> vaparam,
    Shader shparam) : 
    vbo{vbparam}, ebo{ebparam}, vao{vaparam}, shader{shparam} {};
const glm::mat4& Model::getModel()
{
    return model;
}
const VBO& Model::getVBO()
{
    return vbo;
}
const EBO& Model::getEBO()
{
    return ebo;
}
const Shader& Model::getShader()
{
    return shader;
}
void Model::transform(glm::mat4 transform) {
    model += transform;
}
void Model::setContext(void(*func)())
{
    drawFunction = func;
}
void Model::draw()
{
    vbo.get().bind();
    drawFunction();
	int modelLoc = glGetUniformLocation(shader.ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	vao.get().bind();
	ebo.get().draw(&shader);
	vao.get().bind();
}