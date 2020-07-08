#pragma once

#include <glm/vec2.hpp>
#include <vector>

using glm::vec2;

struct entity
{
	/* first 4 elements must be these for rendering purposes */
	float x;
	float y;
	float angle;
	uint8_t team;
};

struct state
{
	std::vector<entity> entities;

	void update(float t, float dt);
};

class simulation
{
	state previous;
	state current;
public:
	void init();
	void update(float t, float dt);
	void get_draw_state(float alpha, state *s);
};

