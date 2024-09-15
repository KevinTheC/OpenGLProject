#pragma once
#include "graphic_structures/Mesh3D.h"
#include "log/Logger.h"
#include "graphic_structures/Shader.h"
#include <string>
#include <functional>
#include "OBJParser.h"
class MeshParser
{
public:
    static Mesh3D* parseMesh(std::string path);
};