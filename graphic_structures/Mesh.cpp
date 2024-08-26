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
	orthographic = true;
    vao->linkAttribs(shader,vbo,ebo);
};
Mesh::~Mesh()
{
    delete(vbo);
    delete(ebo);
    delete(vao);
}
const glm::mat4& Mesh::getModel() const
{
    return model;
}
VBO* Mesh::getVBO() const
{
    return vbo;
}
EBO* Mesh::getEBO() const 
{
    return ebo;
}
std::shared_ptr<Shader> Mesh::getShader() const
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
void Mesh::draw() const
{
    for (int i=0;i<textures.size();i++)
    {
        textures.at(i)->bind(i,GL_TEXTURE_2D);
        textures.at(i)->activate(shader.get(),i);
    }
	if (!orthographic)
    	Camera::instance()->linkShader(shader.get());
    GLuint modelLoc = glGetUniformLocation(shader->ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	vao->bind();
	ebo->draw(geometry);
	vao->unbind();
}

std::string Mesh::toString() const
{
	std::string vbostr;
	std::string matrixstr;
	std::string ebostr;
	std::vector<std::string> outer;
	size_t stride = 1;
	if (geometry == GL_QUADS)
		stride = 4;
	if (geometry == GL_TRIANGLES)
		stride = 3;
	if (geometry == GL_TRIANGLES||geometry == GL_QUADS)
	{
		for (size_t i = 0; i < ebo->getValues().size()/stride; ++i)
		{
			std::vector<std::string> inner;
			for (size_t j = 0; j < stride; ++j)
			{
				inner.push_back(std::to_string(ebo->getValues()[i*stride+j]));
			}
			outer.push_back(MyUtil::arrayifier(inner,false));
		}
		ebostr = MyUtil::arrayifier(outer,true);
	} else
	{
		for (size_t i = 0; i < ebo->getValues().size(); ++i)
			outer.push_back(std::to_string(ebo->getValues()[i]));
		ebostr = MyUtil::arrayifier(outer,false);
	}
	outer.clear();
	stride = 0;
	for (auto attrib : shader->getAttribs())
		stride += attrib;
	for (size_t i = 0; i < vbo->getValues().size()/stride; ++i)
	{
		std::vector<std::string> inner;
		for (size_t j = 0; j < stride; ++j)
		{
			inner.push_back(std::to_string(vbo->getValues()[i*stride+j]));
		}
		outer.push_back(MyUtil::arrayifier(inner,false));
	}
	vbostr = MyUtil::arrayifier(outer,true);
	matrixstr = "[" + std::to_string(model[0][0]) + ", " + std::to_string(model[0][1]) + ", " + std::to_string(model[0][2]) + ", " + std::to_string(model[0][3]) + ",\n";
	matrixstr +=  std::to_string(model[1][0]) + ", " + std::to_string(model[1][1]) + ", " + std::to_string(model[1][2]) + ", " + std::to_string(model[1][3]) + ",\n";
	matrixstr +=  std::to_string(model[2][0]) + ", " + std::to_string(model[2][1]) + ", " + std::to_string(model[2][2]) + ", " + std::to_string(model[2][3]) + ",\n";
	matrixstr +=  std::to_string(model[3][0]) + ", " + std::to_string(model[3][1]) + ", " + std::to_string(model[3][2]) + ", " + std::to_string(model[3][3]) + "]";
	return "VBO: " + vbostr + "\nEBO: " + ebostr + "\nModel Matrix: " + matrixstr;
}