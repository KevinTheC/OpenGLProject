#include "Mesh.h"
Mesh::Mesh(VBO* vbparam,
    EBO* ebparam, 
	VAO* vaparam,
    std::shared_ptr<Shader> shparam,
    uint_fast8_t geometryparam) : 
    vbo{vbparam}, ebo{ebparam}, vao{vaparam}, shader{shparam}, geometry{geometryparam}
{
    model = glm::mat4(1.0f);
    shader->activate();
    vao->linkAttribs(shader,vbo,ebo);
};
Mesh::~Mesh()
{
    delete(vbo);
    delete(ebo);
    delete(vao);
}
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
void Mesh::scale(glm::vec3 scalar)
{
    model = glm::scale(model,scalar);
}
void Mesh::translate(glm::vec3 translation)
{
    model = glm::translate(model,translation);
}
void Mesh::rotate(GLfloat angle, glm::vec3 vect)
{
    model = glm::rotate(model,angle,vect);
}
void Mesh::setContext() const
{
    
}
void Mesh::draw() const
{
    for (int i=0;i<textures.size();i++)
    {
        textures.at(i)->bind(i,GL_TEXTURE_2D);
        textures.at(i)->activate(shader.get(),i);
    }
    Camera::instance()->linkShader(shader.get());
    setContext();
    GLuint modelLoc = glGetUniformLocation(shader->ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	vao->bind();
	ebo->draw(geometry);
	vao->unbind();
}