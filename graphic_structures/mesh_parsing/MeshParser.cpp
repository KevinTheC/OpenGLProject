#include "MeshParser.h"
Mesh* MeshParser::parseMesh(std::string path)
{
    return OBJParser::parse(path);
}