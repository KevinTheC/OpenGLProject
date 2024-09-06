#pragma once
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <cerrno>
#include <vector>
#include <array>
#include "log/logger.h"
std::string get_file_contents(std::string);

class Shader
{
private:
	static GLuint current;
	std::vector<int> attribs;
	Shader(std::string file);
	inline static std::unordered_map<std::string, std::shared_ptr<Shader>> map;
public:
	const GLuint ID = glCreateProgram();
	static std::shared_ptr<Shader> getShader(std::string);
	bool activate();
	void erase();
	void compileError(unsigned int shader, const char* type);
	std::vector<int> getAttribs();
	static void clearCache();
};