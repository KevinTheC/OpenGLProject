#pragma once
#include "Mesh.h"
#include "logger.h"
#include "Shader.h"
#include <string>
#include "OBJParser.h"
class MeshParser {
    static Mesh* parseMesh(std::string path, std::shared_ptr<Shader> sh);
};