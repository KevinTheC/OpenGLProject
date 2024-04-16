#define GLEW_STATIC
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ostream>
#include "log/logger.h"
#include "OpenGLIncludes.h"
#include "objects/Camera.h"
#include "keybinds/InputController.h"
#include "graphic_structures/mesh_parsing/MeshParser.h"
#include "graphic_structures/Mesh.h"
//#define BUILD_TEST

#ifdef LOGGING_DEBUG
void GLAPIENTRY debugCallback(
        GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar* message,
        const void* userParam){
            LOG_DEBUG(message);
        }
#endif



#ifndef BUILD_TEST
#define gray .5f, .5f, .5f,
int height = 900;
int width = 800;

std::vector<std::pair<Mesh*,bool>> drawables;

using namespace glm;
int main()
{
    std::cout << "";
    Logger::initLogger();
    GLFWwindow* window;
    if (!glfwInit())
    {
        LOG_ALERT("GLFW failed to initialize.");
        return -1;
    }
    window = glfwCreateWindow(width, height, "Model", NULL, NULL);
    if (!window)
    {
        LOG_ALERT("GLFW failed to create a window.");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        Logger::log << "glew failed to initialize." << std::endl;
        return -1;
    }
    glViewport(0, 0, width, height);
    #ifdef LOGGING_DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugCallback, nullptr);
    #endif
    Camera::instance()->updateProjection(width, height);
    
    std::shared_ptr<Shader> sh(new Shader("./resources/shaders/test.vert","./resources/shaders/color.frag"));
    sh->activate();
    std::shared_ptr<Shader> sh2(new Shader("./resources/shaders/color.vert","./resources/shaders/color.frag"));
    Mesh mesh2 = Mesh(new VBO(new std::vector<GLfloat>({
        -.2f, 0.4f, -.2f,        gray
        -.2f,  0.4f, .2f,      gray
        .2f,  0.4f, .2f,       gray
        .2f, 0.4f, -.2f, 		gray
        0.0f, 0.8f, 0.0f,		gray
        })),new EBO(new std::vector<GLuint>({
        0U, 1U, 2U,
        0U, 2U, 3U,
        0U, 1U, 4U,
        1U, 2U, 4U,
        2U, 3U, 4U,
        3U, 0U, 4U,
            })),VAO::getVAO(sh2),sh2);
    sh2->activate();
    Mesh* mesh = MeshParser::parseMesh("./resources/meshes/untitled.obj",sh);

    Camera::instance()->setFocus((&mesh2)->getModel());
    Camera::instance()->linkShader(sh2.get());
    //textures
    /*int widthImg, heightImg, numColCh;
    unsigned char* bytes = stbi_load("Untitled.png", &widthImg, &heightImg, &numColCh, 0);
    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint tex0Uni = glGetUniformLocation(shaderprogram.getID(), "tex0");
    shaderprogram.Activate();
    glUniform1i(tex0Uni, 0);
    */
    //textures

    mesh->setContext([](Mesh* curr){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        curr->getShader().get()->activate();
        });
    (&mesh2)->setContext([](Mesh* curr){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        });
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    //drawables.push_back(std::pair<Mesh*,bool>(mesh,true));
    drawables.push_back(std::pair<Mesh*,bool>(&mesh2,true));
    //drawables.push_back(std::pair<Mesh*,bool>(mesh,false));
    drawables.push_back(std::pair<Mesh*,bool>(&mesh2,false));
    glEnable(GL_DEPTH_TEST);

    Camera::instance()->setFocus((&mesh2)->getModel());

    InputController::addObserver(Camera::instance().get());
    glfwSetMouseButtonCallback(window, InputController::GLFWmouseButtonCB);
    glfwSetCursorPosCallback(window, InputController::GLFWmouseMoveCB);
    glfwSetWindowSizeCallback(window, InputController::GLFWresizeCB);
    glfwSetKeyCallback(window, InputController::GLFWkeyCB);
    glfwSetScrollCallback(window, InputController::GLFWmouseWheelCB);
    bool b = true;
    while (!glfwWindowShouldClose(window))
    {
        try {
        LOG_ALL("flag1");
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        LOG_ALL("flag2");
        /* Render here */
        //glBindTexture(GL_TEXTURE_2D, texture);
        //o.transform(glm::vec3(0.0f,0.0f,0.001f));
        // for (const auto& ptr : drawables)
        //     if (ptr.second)
        //         ptr.first->draw();
        mesh2.draw();
        LOG_ALL("flag3");
        glfwSwapBuffers(window);
        LOG_ALL("flag4");
        glfwPollEvents();
        LOG_ALL("flag5");
        } catch (std::exception& e) {
            LOG_DEBUG(e.what());
        }
    }
    sh->erase();
    sh2->erase();
    //glDeleteTextures(1,&texture);
    glfwTerminate();
    return 0;
}
#endif
#ifdef BUILD_TEST
int main()
{
    Logger::initLogger();

    GLFWwindow* window;
    if (!glfwInit())
    {
        Logger::log << "GLFW failed to initialize." << std::endl;
        return -1;
    }
    window = glfwCreateWindow(70, 70, "Model", NULL, NULL);
    if (!window)
    {
        Logger::log << "GLFW failed to create a window." << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        Logger::log << "glew failed to initialize." << std::endl;
        return -1;
    }
    glViewport(0, 0, 70, 70);


    Shader* sh = new Shader("./resources/shaders/color.vert","./resources/shaders/color.frag");
    std::string str;
    auto ty = std::ifstream("./resources/meshes/untitled.obj");
    std::getline(ty,str);
    OBJParser::parse("./resources/meshes/untitled.obj",sh);
}
#endif