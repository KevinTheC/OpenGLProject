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
#define BUILD_TEST

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
    
    std::shared_ptr<Shader> sh(new Shader("./resources/shaders/color.vert","./resources/shaders/color.frag"));
    sh->activate();
    Mesh* mesh = MeshParser::parseMesh("./resources/meshes/untitled.obj",sh);

    Camera::instance()->setFocus(glm::mat4(1.0f));
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

    // mesh->setContext([](Mesh* curr){
    //     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //     curr->getShader().get()->activate();
    //     });
    // (&mesh2)->setContext([](Mesh* curr){
    //     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //     });
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    drawables.push_back(std::pair<Mesh*,bool>(mesh,true));
    // drawables.push_back(std::pair<Mesh*,bool>(&mesh2,true));
    // //drawables.push_back(std::pair<Mesh*,bool>(mesh,false));
    // drawables.push_back(std::pair<Mesh*,bool>(&mesh2,false));
    glEnable(GL_DEPTH_TEST);

    InputController::addObserver(Camera::instance().get());
    glfwSetMouseButtonCallback(window, InputController::GLFWmouseButtonCB);
    glfwSetCursorPosCallback(window, InputController::GLFWmouseMoveCB);
    glfwSetWindowSizeCallback(window, InputController::GLFWresizeCB);
    glfwSetKeyCallback(window, InputController::GLFWkeyCB);
    glfwSetScrollCallback(window, InputController::GLFWmouseWheelCB);
    GLuint highest = 0;
    for (const auto& val : (*mesh->getEBO()).getValues())
        if (val > highest)
            highest = val;
    LOG_ALL(std::to_string(highest));
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        /* Render here */

        //glBindTexture(GL_TEXTURE_2D, texture);
        //o.transform(glm::vec3(0.0f,0.0f,0.001f));
        for (const auto& ptr : drawables)
            if (ptr.second)
                ptr.first->draw();
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



	std::shared_ptr<Shader> sh(new Shader("./resources/shaders/original.vert","./resources/shaders/original.frag"));


    VBO vbo = VBO(new std::vector<GLfloat>({
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, gray// Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, gray// Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, gray// Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, gray// Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, gray// Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f, gray// Inner down
	}));
	// Indices for vertices order
    EBO ebo = EBO(new std::vector<GLuint>({
        0, 3, 5, // Lower left triangle
		3, 2, 4, // Upper triangle
		5, 4, 1  // Lower right triangle
    }));

    
	// Create reference containers for the Vertex Array Object, the Vertex Buffer Object, and the Element Buffer Object
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
    
    vbo.bind();
    ebo.bind();
    // VAO vao = VAO(sh);
    // vao.linkAttribs(sh,&vbo);
	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	// glBindBuffer(GL_ARRAY_BUFFER, vboi);
	
	// Introduce the indices into the EBO

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
	glEnableVertexAttribArray(1);

	vbo.unbind();
    glBindVertexArray(0);
	// vao.unbind();
	ebo.unbind();



	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		glUseProgram(sh.get()->ID);

		glBindVertexArray(VAO);
        // vao.bind();
        LOG_ALL("MINECRAFT");
        ebo.draw(GL_TRIANGLES);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
    // vao.erase();
	// glDeleteVertexArrays(1, &VAO);
	vbo.erase();
	ebo.erase();
	glDeleteProgram(sh.get()->ID);
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}
#endif