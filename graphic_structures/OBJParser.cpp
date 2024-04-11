#include "OBJParser.h"
Model OBJParser::parse(std::string path, Shader sh)
{
    std::vector<glm::vec3> prevertex;
    std::unordered_map<glm::vec3,int_fast16_t> prevertexmap;
    std::vector<glm::vec2> pretexture;
    std::unordered_map<glm::vec2,int_fast16_t> pretexturemap;
    for (const glm::vec3& v : prevertex)
    {
        std::cout << v[0] << v[1] << v[2] << std::endl;
    }
    std::ifstream stream(path);
    std::vector<Vertex>* faces = new std::vector<Vertex>();
    //the vertex UV pair the face is pointing to will not be at a constant position. therefore, we need to first read all UV mappings and vertexes, then use the hashmap to O(1) access
    //the vertex and UV indexes, and generate the VBO's representation of the pair. Afterwards, we will determine the position at which face the ebo should point. EBO will be in quad format
    std::vector<Vertex>* vertexes = new std::vector<Vertex>();
    std::unordered_map<Vertex,int_fast16_t> vertexmap;
}
void OBJParser::getVertexes(std::ifstream& stream, std::vector<glm::vec3>& prephase)
{
    std::string line;
    line[0] = 'b';
    while (line[0]!='v')
        std::getline(stream,line);
    do {
        int ptr = 3;




        std::getline(stream,line);
    } while (line[1]!='t');
}