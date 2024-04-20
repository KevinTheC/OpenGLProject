#pragma once
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include "Shader.h"
#include "stb_image.h"
#include "include/GL/glew.h"
#include "log/logger.h"
class Texture{
private:
    GLuint ID;
    Texture(std::string);
    inline static std::unordered_map<std::string,Texture> map;
public:
    static Texture& getTexture(std::string);
    Texture& bind(int offset,int type);
    void activate(Shader*,int);
    static void clear(int);
    void erase();
};