#pragma once
#include <stdlib.h>
#include <array>
#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "graphic_structures/EBO.h"
#include "graphic_structures/VBO.h"
#include "graphic_structures/VAO.h"
#include "graphic_structures/Mesh.h"
typedef struct BufferPointers{
    std::reference_wrapper<VBO> vbo;
    std::reference_wrapper<EBO> ebo;
} BufferPointers;
class OBJParser{
public:
    static Mesh* parse(std::string path, std::shared_ptr<Shader> sh);
private:
    static void getVertexes(std::ifstream stream, std::vector<glm::vec3>& prephase, std::unordered_map<int_fast16_t,glm::vec3>& premap);
    static void getUVs(std::ifstream stream, std::vector<glm::vec2>& prephase, std::unordered_map<int_fast16_t,glm::vec2>& premap);
    static std::vector<std::string> splitString(std::string, char);
};
