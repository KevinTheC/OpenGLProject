#define GLEW_STATIC
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ostream>
#include "log/logger.h"
#include "OpenGLIncludes.h"
#include "objects/Camera.h"
#include "objects/UIManager.h"
#include "objects/InterfaceFactory.h"
#include "graphic_structures/fonts/FontTextureAtlas.h"
#include "keybinds/InputController.h"
#include "graphic_structures/mesh_parsing/MeshParser.h"
#include "graphic_structures/Mesh.h"
#include "graphic_structures/Texture.h"
#include "graphic_structures/interfaces/InterfaceTextureAtlas.h"

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


int height = 900;
int width = 800;

std::vector<Mesh*> drawables;

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
        LOG_ALERT("glew failed to initialize.");
        return -1;
    }
    glViewport(0, 0, width, height);
    #ifdef LOGGING_DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugCallback, nullptr);
    #endif
    
    Mesh* mesh = MeshParser::parseMesh("./resources/meshes/test.obj");
    drawables.push_back(mesh);
    LOG_ALL(Logger::toString(*mesh));
    //drawables.push_back(poop);
    // 	Mesh(VBO&&,
	// EBO&&, 
	// VAO&&,
	// std::shared_ptr<Shader>,
	// uint_fast8_t);
    // delete(mesh->getVBO());
    // delete(mesh->getVAO());
    // delete(mesh->getEBO());



    Camera::instance()->updateProjection(width, height);
    Camera::instance()->setFocus(glm::mat4(1.0f));

    UIManager::instance()->registerUI(InterfaceFactory::defaultInterface());
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);


    InputController::addObserver(Camera::instance().get());
    InputController::addObserver(UIManager::instance().get());
    glfwSetMouseButtonCallback(window, InputController::GLFWmouseButtonCB);
    glfwSetCursorPosCallback(window, InputController::GLFWmouseMoveCB);
    glfwSetWindowSizeCallback(window, InputController::GLFWresizeCB);
    glfwSetKeyCallback(window, InputController::GLFWkeyCB);
    glfwSetScrollCallback(window, InputController::GLFWmouseWheelCB);

    try
    {
        while (!glfwWindowShouldClose(window))
        {
            glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            for (const auto& val : drawables)
                val->draw();
            UIManager::instance()->draw();
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    } catch (const std::exception& e) {
        LOG_ALERT(std::string("Crashed! Exception thrown: ")+e.what());
    } catch (...) {
        LOG_ALERT("Crashed! Unknown Exception thrown");
    }
    Shader::clearCache();
    glfwTerminate();
    return 0;
}