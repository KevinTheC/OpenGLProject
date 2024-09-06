#pragma once
#include <stdlib.h>
#include <array>
#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "utils/Util.h"
#include "graphic_structures/EBO.h"
#include "graphic_structures/VBO.h"
#include "graphic_structures/VAO.h"
#include "graphic_structures/Mesh.h"
#include "graphic_structures/Texture.h"
class OBJParser{
public:
    static Mesh* parse(std::string path);
private:
    static void getVertexes(std::ifstream stream, std::vector<glm::vec3>& prephase, std::unordered_map<int_fast16_t,glm::vec3>& premap);
    static void getUVs(std::ifstream stream, std::vector<glm::vec2>& prephase, std::unordered_map<int_fast16_t,glm::vec2>& premap);
    static std::string changeExtension(std::string);
    static void loadTextures(std::ifstream stream, Mesh* mesh);
};
