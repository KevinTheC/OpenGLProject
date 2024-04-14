#include "OBJParser.h"
Mesh* OBJParser::parse(std::string path, std::shared_ptr<Shader> sh)
{
    LOG_DEBUG(std::string("Parsing a shader at: ")+path);
    std::vector<glm::vec3> prevertex;
    std::unordered_map<int_fast16_t,glm::vec3> prevertexmap;
    std::vector<glm::vec2> pretexture;
    std::unordered_map<int_fast16_t,glm::vec2> pretexturemap;

    OBJParser::getVertexes(std::ifstream(path),prevertex,prevertexmap);
    LOG_DEBUG(std::string("Vertexes parsed"));
    OBJParser::getUVs(std::ifstream(path),pretexture,pretexturemap);
    LOG_DEBUG(std::string("UVs parsed"));
    //the vertex UV pair the face is pointing to will not be at a constant position. therefore, we need to first read all UV mappings and vertexes, then use the hashmap to O(1) access
    //the vertex and UV indexes, and generate the VBO's representation of the pair. Afterwards, we will determine the position at which face the ebo should point. EBO will be in quad format
    std::vector<GLuint>* faces = new std::vector<GLuint>();
    
    std::vector<Vertex>* vertexes = new std::vector<Vertex>();
    std::unordered_map<Vertex,int_fast16_t> vertexmap;

    std::string line;
    auto stream = std::ifstream(path);
    std::getline(stream,line);
    while (line[0]!='f')
        std::getline(stream,line);
    //ifstream loaded up to faces
    int i = 0;
    do {
        std::istringstream str{line};
        std::string f;
        Vertex v;
        str >> f;
        //parse the face
        for (int j=0;j<4;j++)
        {
            str >> f;
            auto vec = splitString(f,'/');
            #ifdef LOG_ALL
            for (const auto& r : vec)
                LOG_ALL(r);
            #endif
            try {
                v.position = prevertexmap.at(std::stoi(vec[0]));
                v.UV = pretexturemap.at(std::stoi(vec[1]));
            } catch (...) {
                LOG_DEBUG(std::string("Failed to parse a face at ")+path+std::string(". Face: ") + line);
            }
            if (vertexmap.find(v) != vertexmap.end())
                faces->push_back(vertexmap.at(v));
            else
            {
                vertexes->push_back(v);
                vertexmap.emplace(v,i++);
            }
            std::getline(stream,line);
            LOG_ALL(std::string("Face parsed"));
        }
    } while (!line.empty());
    LOG_DEBUG("Mesh Parsed.");
    //INTENTIONAL CRASHING
    EBO* ebo = new EBO(faces);
    VBO* vbo = new VBO(vertexes);
    Mesh* ptr = new Mesh(vbo,ebo,VAO::getVAO(sh),sh);
    return ptr;
}


void OBJParser::getVertexes(std::ifstream stream,
std::vector<glm::vec3>& prephase,
std::unordered_map<int_fast16_t,glm::vec3>& premap)
{
    std::string line;
    //don't know how string works under the hood so I do this just incase im reading uninitialized memory
    std::getline(stream,line);
    while (line[0]!='v')
        std::getline(stream,line);
    int i = 1;
    do {
        std::istringstream str(line);
        glm::vec3 vec;
        std::string f;
        str >> f;
        for (int j=0;j<3;j++)
        {
            str >> f;
            vec[j] = std::stof(f);
        }
            
        prephase.push_back(vec);
        premap.emplace(i++,vec);
        std::getline(stream,line);
    } while (line[1]!='n');
}


void OBJParser::getUVs(std::ifstream stream,
std::vector<glm::vec2>& prephase,
std::unordered_map<int_fast16_t,glm::vec2>& premap)
{
    std::string line;
    //don't know how string works under the hood so I do this just incase im reading uninitialized memory
    std::getline(stream,line);
    while (line[1]!='t'||line[0]!='v')
        std::getline(stream,line);
    int i = 1;
    do {
        std::istringstream str(line);
        glm::vec2 vec;
        std::string f;
        str >> f;
        for (int j=0;j<2;j++)
        {
            str >> f;
            vec[j] = std::stof(f);
        }
            
        prephase.push_back(vec);
        premap.emplace(i++,vec);
        std::getline(stream,line);
    } while (line[0]!='s');
}

std::vector<std::string> OBJParser::splitString(std::string str, char delimiter)
{
    std::vector<std::string> retvec;
    size_t slow = 0;
    size_t fast = 1;
    while (fast < str.length())
    {
        if (str[fast] == delimiter)
        {
            if (fast != slow)
                retvec.push_back(str.substr(slow, fast - slow));
            slow = ++fast;
        }
        else
            ++fast;
    }
    if (fast != slow)
        retvec.push_back(str.substr(slow, fast));
    return retvec;
};