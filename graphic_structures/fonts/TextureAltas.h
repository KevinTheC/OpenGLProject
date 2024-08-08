#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <vector>
#include "TextMesh.h"
namespace TextureAtlas
{
TextMesh* buildText(std::shared_ptr<Shader>, std::string, std::array<GLfloat, 3>);
std::array<GLfloat, 8> UVTable(char);
};