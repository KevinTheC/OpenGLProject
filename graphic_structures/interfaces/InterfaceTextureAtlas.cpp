#include "InterfaceTextureAtlas.h"
Mesh* InterfaceTextureAtlas::buildUI(const std::string& file)
{
    std::vector<GLuint>* faces = new std::vector<GLuint>();
    std::vector<GLfloat>* vertexes = new std::vector<GLfloat>();
    GLfloat x = -0.5f;
    GLfloat y = -0.5f;
    std::array<GLfloat, 8> UVs = {0.0f,1.0f,1.0f,1.0f,0.0f,0.0f,1.0f,0.0f};
    std::array<GLfloat, 8> XYZs = {-1.0f,-1.0f,1.0f,-1.0f,-1.0f,1.0f,1.0f,1.0f};
    for (size_t j = 0; j<8; j+=2)
    {
        vertexes->push_back(XYZs[j]);
        vertexes->push_back(XYZs[j+1]);
        vertexes->push_back(UVs[j]);
        vertexes->push_back(UVs[j+1]);
    }
    faces->push_back(0);
    faces->push_back(2);
    faces->push_back(3);
    faces->push_back(1);
    std::shared_ptr<Shader> shader = Shader::getShader(std::string("./resources/shaders/singleTexture"));
    Mesh* ptr = new TextMesh(new VBO(vertexes),new EBO(faces),new VAO(shader),shader,GL_QUADS);
    ptr->textures.push_back(&Texture::getTexture(file));
    ptr->orthographic = true;
    return ptr;
}