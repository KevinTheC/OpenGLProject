#pragma once
#include <stdlib.h>
#include <string>
#include "graphic_structures/Mesh.h"
#include <stdint.h>
class TextGenerator{
    Mesh* generateText(std::string, uint_fast8_t);
};