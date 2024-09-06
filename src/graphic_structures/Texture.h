#pragma once
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include "Shader.h"
#include "stb_image.h"
#include "OpenGLIncludes.h"
#include "log/logger.h"
class Texture{
private:
    GLuint ID;
    Texture(std::string);
    inline static std::unordered_map<std::string,std::shared_ptr<Texture>> map;
public:
    static std::shared_ptr<Texture> getTexture(std::string);
    Texture* bind(int offset,int type);
    void activate(std::shared_ptr<Shader>,int);
    static void clear(int);
    void erase();
};