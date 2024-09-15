#pragma once
#include <stdlib.h>
#include <vector>
#include "OpenGLIncludes.h"
class Hitbox{
public:
    std::vector<glm::vec3> corners;
	Hitbox(std::vector<glm::vec3>&& vec)
        : corners(std::move(vec)) {}

	Hitbox(const Hitbox& other)
		: corners(other.corners) {}
	Hitbox(Hitbox&& other) noexcept
		: corners(std::move(other.corners)) {}
	Hitbox& operator=(const Hitbox& other)
	{
		return *this = Hitbox(other);
	}
	Hitbox& operator=(Hitbox&& other) noexcept
	{
		std::swap(corners, other.corners);
		return *this;
	}
};