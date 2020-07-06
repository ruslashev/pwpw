#pragma once

#include <glm/vec2.hpp>
#include <vector>

using glm::vec2;

struct entity
{
	/* first 3 elements must be these for rendering purposes */
	float x;
	float y;
	float angle;
};

struct state
{
	std::vector<entity> entities;

	void update(float t, float dt);
};

void interpolate_states(const state &s1, const state &s2, float t, state *out);

