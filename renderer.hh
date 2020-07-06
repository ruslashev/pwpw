#pragma once

#include <glm/mat4x4.hpp>
#include "opengl.hh"
#include "simulation.hh"

using glm::mat4;

class camera
{
	float scale;

	void calculate_viewmat();
public:
	mat4 view;

	camera();
	void change_scale(float diff);
};

class renderer
{
	vao va;
	buffer vertices;
	buffer elements;
	buffer instances;
	shprog shp;

	camera cam;

	int uni_proj_id;
	int uni_view_id;
public:
	void init(int w, int h);
	void render(const state *s);
	void scroll(float diff);
	~renderer();
};

