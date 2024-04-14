#include "MeshParser.h"
Mesh* MeshParser::parseMesh(std::string path, std::shared_ptr<Shader> sh)
{
    //theres not really any files other than obj but one day
    return OBJParser::parse(path,sh);
}