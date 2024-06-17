#include "OBJParser.h"
Mesh* OBJParser::parse(std::string path, std::shared_ptr<Shader> sh)
{
    LOG_DEBUG(std::string("Parsing a mesh at: ")+path);

    std::vector<glm::vec3> prevertex;
    std::unordered_map<int_fast16_t,glm::vec3> prevertexmap;
    std::vector<glm::vec2> pretexture;
    std::unordered_map<int_fast16_t,glm::vec2> pretexturemap;

    OBJParser::getVertexes(std::ifstream(path),prevertex,prevertexmap);

    LOG_DEBUG(std::string("Vertexes parsed"));
    LOG_ALL(std::string("Count: ")+std::to_string(prevertex.size()));

    OBJParser::getUVs(std::ifstream(path),pretexture,pretexturemap);

    LOG_DEBUG(std::string("UVs parsed"));
    LOG_ALL(std::string("Count: ")+std::to_string(pretexture.size()));

    //the vertex UV pair the face is pointing to will not be at a constant position. therefore, we need to first read all UV mappings and vertexes, then use the hashmap to O(1) access
    //the vertex and UV indexes, and generate the VBO's representation of the pair. Afterwards, we will determine the position at which face the ebo should point. EBO will be in quad format
    std::vector<GLuint>* faces = new std::vector<GLuint>();
    std::vector<Vertex>* vertexes = new std::vector<Vertex>();
    std::unordered_map<Vertex,int_fast16_t> vertexmap;

    std::string line;
    auto stream = std::ifstream(path);
    std::getline(stream,line);
    
    while (line[0]!='u')
        std::getline(stream,line);
    //ifstream loaded up to faces

    size_t i = 0;
    size_t textnum = 0;
    do {
        std::getline(stream,line);
        if (line[0]=='u')
        {
            ++textnum;
            continue;
        }

        std::istringstream str{line};
        std::string f;
        Vertex v;
        str >> f;
        //parse the face
        for (int j=0;j<4;j++)
        {
            str >> f;
            auto vec = MyUtil::splitString(f,'/');
            try {
                v.position = prevertexmap.at(std::stoi(vec[0]));
                v.UV = pretexturemap.at(std::stoi(vec[1]));
                v.index = textnum;
            } catch (...) {
                LOG_DEBUG(std::string("Failed to parse a face at ")+path+std::string(". Face: ") + line);
            }
            if (vertexmap.find(v) != vertexmap.end())
                faces->push_back(vertexmap.at(v));
            else
            {
                vertexes->push_back(v);
                faces->push_back(i);
                vertexmap.emplace(v,i++);
            }
        }
    } while (stream.peek()!=EOF);
    LOG_DEBUG("Mesh Parsed.");
    EBO* ebo = new EBO(faces);
    LOG_ALL(faces->size());
    std::vector<GLfloat>* floats = new std::vector<GLfloat>();
    for (i=0;i<vertexes->size();i++)
    {
        floats->push_back(vertexes->at(i).position[0]);
        floats->push_back(vertexes->at(i).position[1]);
        floats->push_back(vertexes->at(i).position[2]);
        floats->push_back(vertexes->at(i).UV[0]);
        floats->push_back(vertexes->at(i).UV[1]);
        floats->push_back(vertexes->at(i).index);
    }
    VBO* vbo = new VBO(floats);
    Mesh* ptr = new Mesh(vbo,ebo,new VAO(sh),sh,GL_QUADS);

    //Load references for textures into Mesh
    loadTextures(std::ifstream(changeExtension(path)),ptr);
    ptr->setContext([](const Mesh* mesh){
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    });

    LOG_ALL(std::string("Size of EBO, then VBO:" )+std::to_string(ebo->getValues().size())+std::string(", ")+std::to_string(vbo->getValues().size()));
    return ptr;
}


std::string OBJParser::changeExtension(std::string oldpath)
{
    return oldpath.substr(0,oldpath.find('.',oldpath.size()-5)) + std::string(".mtl");
}
void OBJParser::loadTextures(std::ifstream stream, Mesh* ptr)
{
    LOG_ALL("Parsing Textures");
    std::string line;
    do {
        std::getline(stream,line);
        std::istringstream str(line);
        std::string f;
        str >> f;
        if (f.find("map_Kd") != std::string::npos)
        {
            str >> f;
            auto vec = MyUtil::splitString(f,'/');
            f = vec[vec.size()-1];
            ptr->textures.push_back(&Texture::getTexture(std::string("./resources/textures/")+f));
            LOG_ALL(ptr->textures.size());
        }
    } while (stream.peek()!=EOF);
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
