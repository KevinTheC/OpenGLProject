#include "FontTextureAtlas.h"
TextMesh* FontTextureAtlas::buildText(const std::string& text, std::array<GLfloat, 3> rgb)
{
    std::vector<GLuint> faces = std::vector<GLuint>();
    std::vector<GLfloat> vertexes = std::vector<GLfloat>();
    GLfloat x = -0.5f;
    GLfloat y = -0.5f;
    for (size_t i = 0; i<text.size(); ++i)
    {
        if (text[i]!='\n')
        {
            y=-0.5f;
            x+=0.1f;
        }
        std::array<GLfloat, 8> UVs = UVTable(text[i]);
        std::array<GLfloat, 8> XYZs = {x,y,x+0.09f,y,x,y+0.09f,x+0.09f,y+0.09f};
        for (size_t j = 0; j<8; j+=2)
        {
            vertexes.push_back(XYZs[j]);
            vertexes.push_back(XYZs[j+1]);
            vertexes.push_back(UVs[j]);
            vertexes.push_back(UVs[j+1]);
        }
        y+=0.1f;
    }
    for (size_t i = 0; i<text.size()*4; i+=4)
    {
        faces.push_back(i);
        faces.push_back(i+2);
        faces.push_back(i+3);
        faces.push_back(i+1);
    }
    std::shared_ptr<Shader> shader = Shader::getShader(std::string("./resources/shaders/coloredText"));
    TextMesh* ptr = new TextMesh(new VBO(std::move(vertexes)),new EBO(std::move(faces)),new VAO(shader),shader,GL_QUADS);
    ptr->setColor(rgb);
    ptr->textures.push_back(&Texture::getTexture(std::string("./resources/textures/fonts/consolasTransparent.png")));
    return ptr;
}
std::array<GLfloat, 8> FontTextureAtlas::UVTable(char c)
{
    int index = c-'A';
    constexpr float xmultiplier = 34.0f/432.0f;
    constexpr float ymultiplier = 1.0f/6.0f;
    if (c == ' ')
        index = 26;
    std::array<GLfloat, 8> returnValue;
    returnValue[0] = xmultiplier*(index%5);
    returnValue[1] = ymultiplier*(index/5+1);
    returnValue[2] = xmultiplier*(index%5+1);
    returnValue[3] = ymultiplier*(index/5+1);
    returnValue[4] = xmultiplier*(index%5);
    returnValue[5] = ymultiplier*(index/5);
    returnValue[6] = xmultiplier*(index%5+1);
    returnValue[7] = ymultiplier*(index/5);
    return returnValue;
}