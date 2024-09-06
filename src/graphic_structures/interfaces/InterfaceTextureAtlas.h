#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <vector>
#include "graphic_structures/fonts/TextMesh.h"
#define screensize 3.0971f
namespace InterfaceTextureAtlas
{
    Mesh2D* buildUI(const std::string&);
};