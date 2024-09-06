#pragma once
#include "graphic_structures/Mesh.h"
#include "log/Logger.h"
#include "graphic_structures/Shader.h"
#include <string>
#include <functional>
#include "OBJParser.h"
class MeshParser
{
public:
    static Mesh* parseMesh(std::string path);
};