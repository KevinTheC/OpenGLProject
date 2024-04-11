#pragma once
#include <stdlib.h>
#include <array>
#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "EBO.h"
#include "VBO.h"
#include "VAO.h"
#include "Model.h"
typedef struct BufferPointers{
    std::reference_wrapper<VBO> vbo;
    std::reference_wrapper<EBO> ebo;
} BufferPointers;
class OBJParser{
public:
    static Model parse(std::string path, Shader sh);
private:
    void getVertexes(std::ifstream& stream, std::vector<glm::vec3>& prephase);
    void getUVs(std::ifstream& stream, std::vector<glm::vec2>& prephase);
};
