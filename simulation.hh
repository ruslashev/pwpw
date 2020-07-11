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

	float vel_x;
	float vel_y;

	float acc_x;
	float acc_y;

	void update(float t, float dt);
};

typedef std::vector<entity> entlist;

struct state
{
	entlist entities;
	entlist bullets;

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

