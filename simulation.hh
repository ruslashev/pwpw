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

void interpolate_states(const state &s1, const state &s2, double t, state *out);

