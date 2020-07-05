#pragma once

#include <glm/vec2.hpp>
#include <vector>

using glm::vec2;

struct ship
{
	vec2 position;
	float angle;
};

struct state
{
	std::vector<ship> ships;
};

