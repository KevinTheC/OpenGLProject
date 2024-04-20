#include "Texture.h"
Texture::Texture(std::string path)
{
    int width,height,colch;
    unsigned char* bytes = stbi_load(path.c_str(), &width, &height, &colch, 0);
    if ((uintptr_t)bytes == (uintptr_t)"can't fopen" || (uintptr_t)bytes == (uintptr_t)"Unable to open file")
        LOG_ALERT(std::string("No texture found at ")+path);
    glGenTextures(1, &ID);
    bind(GL_TEXTURE0,GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    stbi_image_free(bytes);
    glGenerateMipmap(GL_TEXTURE_2D);
    //clear(GL_TEXTURE0);
}
Texture& Texture::getTexture(std::string path)
{
    if (map.find(path)!=map.end())
        return map.at(path);
    map.emplace(path,Texture(path));
    return map.at(path);
}
Texture& Texture::bind(int loc, int type = GL_TEXTURE_2D)
{
    glActiveTexture(GL_TEXTURE0+loc);
    glBindTexture(type,ID);
    return *this;
}
void Texture::activate(Shader* ptr,int index)
{
    ptr->activate();
    GLuint loc = glGetUniformLocation(ptr->ID,(std::string("tex[")+std::to_string(index)+std::string("]")).c_str());
    glUniform1i(loc, 0);
}
void Texture::clear(int loc)
{
    glBindTexture(loc,0);
}
void Texture::erase()
{
    glDeleteTextures(1,&ID);
}