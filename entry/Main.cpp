#define GLEW_STATIC
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ostream>
#include "log/logger.h"
#include "OpenGLIncludes.h"
#include "objects/Camera.h"
#include "objects/UIManager.h"
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

std::vector<std::pair<Mesh*,bool>> drawables;

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
    #ifdef LOGGING_DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugCallback, nullptr);
    #endif
    
    std::shared_ptr<Shader> sh = Shader::getShader(std::string("./resources/shaders/texture"));
    TextMesh* text = FontTextureAtlas::buildText("HELLO WORLDD", std::array<GLfloat, 3>{0.0f,0.0f,0.4f});
    text->setOffset(std::array<GLfloat, 3>{0.0f,0.0f,0.0f});
    Mesh* mesh = MeshParser::parseMesh("./resources/meshes/test.obj",sh);
    Mesh* inter = InterfaceTextureAtlas::buildUI("./resources/textures/broThinkhePregnant.png");
    
    drawables.push_back(std::pair<Mesh*,bool>(inter,true));



    mesh->scale(glm::vec3(0.1f,0.1f,0.1f));
    mesh->translate(glm::vec3(1.0f,0.0f,0.0f));
    
    drawables.push_back(std::pair<Mesh*,bool>(mesh,true));
    drawables.push_back(std::pair<Mesh*,bool>(text,true));

    Camera::instance()->updateProjection(width, height);
    Camera::instance()->setFocus(glm::mat4(1.0f));
    Camera::instance()->linkShader(sh.get());


    //Mesh* mesh2 = MeshParser::parseMesh("./resources/meshes/test.obj",sh);
    //UIManager::instance()->registerUI(new Interface(mesh,std::vector<Area>(),std::vector<Event>({Test2})));

    //drawables.push_back(std::pair<Mesh*,bool>(mesh2,true));

    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );

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
                if (val.second)
                    val.first->draw();
            UIManager::instance()->draw();
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    } catch (const std::exception& e) {
        LOG_ALERT(std::string("Crashed! Exception thrown: ")+e.what());
    } catch (...) {
        LOG_ALERT("Crashed! Unknown Exception thrown");
    }
    sh->erase();
    glfwTerminate();
    return 0;
}