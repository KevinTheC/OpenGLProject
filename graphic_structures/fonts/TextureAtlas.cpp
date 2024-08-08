#include "TextureAltas.h"
TextMesh* TextureAtlas::buildText(std::shared_ptr<Shader> shader, std::string text, std::array<GLfloat, 3> rgb)
{
    std::vector<GLuint>* faces = new std::vector<GLuint>();
    std::vector<GLfloat>* vertexes = new std::vector<GLfloat>();
    GLfloat y = 0;
    GLfloat x = 0;
    for (size_t i = 0; i<text.size(); ++i)
    {
        if (text[i]!='\n')
        {
            y++;
            x=-1;
        }
        std::array<GLfloat, 8> UVs = UVTable(text[i]);
        std::array<GLfloat, 8> XYZs = {x,y,x+0.9,y,x,y+0.9,x+0.9,y+0.9};
        for (size_t j = 0; j<8; j+=2)
        {
            vertexes->push_back(XYZs[j]);
            vertexes->push_back(XYZs[j+1]);
            vertexes->push_back(0.0);
            vertexes->push_back(UVs[j]);
            vertexes->push_back(UVs[j+1]);
        }
        x+=1;
    }
    for (size_t i = 0; i<text.size()*4; ++i)
        faces->push_back(i);
    TextMesh* ptr = new TextMesh(new VBO(vertexes),new EBO(faces),new VAO(shader),shader,GL_QUADS);
    ptr->setColor(rgb);
    return ptr;
}
std::array<GLfloat, 8> TextureAtlas::UVTable(char c)
{
    int index = 'A'-c;
    if (c == ' ')
        index = 26;
    std::array<GLfloat, 8> returnValue;
    returnValue[0] = index%5;
    returnValue[1] = index/5;
    returnValue[2] = index%5+1;
    returnValue[3] = index/5;
    returnValue[4] = index%5;
    returnValue[5] = index/5+1;
    returnValue[6] = index%5+1;
    returnValue[7] = index/5+1;
    return returnValue;
}