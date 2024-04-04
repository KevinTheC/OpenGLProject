#include "graphic_structures/Model.h"
Model::Model(std::string path, Shader sh)
{
   model = glm::mat4(1.0f);
   ebo = NULL;
   vbo = NULL;
   vao = VAO::getVAO(sh);
}
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
    vbo.bind();
    drawFunction();
	int modelLoc = glGetUniformLocation(shader.ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	vao.bind();
	ebo.draw(&shader);
	vao.bind();
}