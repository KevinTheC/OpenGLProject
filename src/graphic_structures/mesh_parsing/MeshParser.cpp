#include "MeshParser.h"
Mesh3D* MeshParser::parseMesh(std::string path)
{
    return OBJParser::parse(path);
}