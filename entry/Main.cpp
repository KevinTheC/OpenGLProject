#define GLEW_STATIC
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ostream>
#include "log/logger.h"
#include "OpenGLIncludes.h"
#include "objects/Camera.h"
#include "objects/UIManager.h"
#include "graphic_structures/fonts/test.h"
#include "keybinds/InputController.h"
#include "graphic_structures/mesh_parsing/MeshParser.h"
#include "graphic_structures/Mesh.h"
#include "graphic_structures/Texture.h"
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


#define gray .5f, .5f, .5f,
#ifndef BUILD_TEST
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
    
    std::shared_ptr<Shader> sh(new Shader("./resources/shaders/texture.vert","./resources/shaders/texture.frag"));
    std::shared_ptr<Shader> textshader(new Shader("./resources/shaders/coloredText.vert","./resources/shaders/coloredText.frag"));
    TextMesh* text = TextureAtlas::buildText(textshader,std::string("Hello World"), std::array<GLfloat,3>{1.0f,0.0f,0.0f});
    Mesh* mesh = MeshParser::parseMesh("./resources/meshes/test.obj",sh);
    mesh->scale(glm::vec3(0.1f,0.1f,0.1f));
    mesh->translate(glm::vec3(1.0f,0.0f,0.0f));

    drawables.push_back(std::pair<Mesh*,bool>(text,true));


    Camera::instance()->updateProjection(width, height);
    Camera::instance()->setFocus(glm::mat4(1.0f));
    Camera::instance()->linkShader(sh.get());


    //Mesh* mesh2 = MeshParser::parseMesh("./resources/meshes/test.obj",sh);
    UIManager::instance()->registerUI(new Interface(mesh,std::vector<Area>(),std::vector<Event>({Test2})));

    //drawables.push_back(std::pair<Mesh*,bool>(mesh2,true));

    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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
    window = glfwCreateWindow(800, 800, "Model", NULL, NULL);
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
    glViewport(0, 0, 800, 800);


    std::shared_ptr<Shader> sh3(new Shader("./resources/shaders/original.vert","./resources/shaders/original.frag"));       
    std::shared_ptr<Shader> sh(new Shader("./resources/shaders/test.vert","./resources/shaders/color.frag"));
    Mesh* mesh = MeshParser::parseMesh("./resources/meshes/untitled.obj",sh3);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
        mesh->draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	sh3->erase();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}
#endif