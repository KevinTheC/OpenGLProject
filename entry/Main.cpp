#define GLEW_STATIC
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ostream>
#include "log/logger.h"
#include "OpenGLIncludes.h"
#include "objects/Camera.h"
#include "keybinds/InputController.h"
#include "graphic_structures/OBJParser.h"
#include "graphic_structures/Mesh.h"
//#define BUILD_TEST

#ifndef BUILD_TEST
#define gray .5f, .5f, .5f,
int height = 900;
int width = 800;

using namespace glm;
int main()
{
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
    Camera::instance()->updateProjection(width, height);
    
    //vertices for triangle
    //Shader shaderprogram("default.vert","default.frag");
    std::shared_ptr<Shader> sh(new Shader("./resources/shaders/color.vert","./resources/shaders/color.frag"));
    sh->activate();

    Mesh* mesh = OBJParser::parse("./resources/meshes/untitled.obj",sh);
    Camera::instance()->setFocus(mesh->getModel());
    Camera::instance()->linkShader(sh.get());
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
    mesh->setContext([](){glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);});
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    
    glEnable(GL_DEPTH_TEST);
    //Object* object = CubeFactory::generate(glm::vec3(0.0f, 0.0f, 0.0f), .2f, {red},sh);
    //object->setContext();
    InputController::addObserver(Camera::instance().get());
    glfwSetMouseButtonCallback(window, InputController::GLFWmouseButtonCB);
    glfwSetCursorPosCallback(window, InputController::GLFWmouseMoveCB);
    glfwSetWindowSizeCallback(window, InputController::GLFWresizeCB);
    glfwSetKeyCallback(window, InputController::GLFWkeyCB);
    glfwSetScrollCallback(window, InputController::GLFWmouseWheelCB);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        /* Render here */
        //glBindTexture(GL_TEXTURE_2D, texture);
        //o.transform(glm::vec3(0.0f,0.0f,0.001f));
        Renderable::drawAll();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    sh->erase();
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