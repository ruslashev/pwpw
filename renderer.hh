#pragma once

#include <glm/mat4x4.hpp>
#include "opengl.hh"
#include "simulation.hh"

using glm::mat4;

class camera
{
	float offset_x;
	float offset_y;
	float scale;

	void calculate_viewmat();
public:
	mat4 view;

	camera();
	void change_scale(float diff);
	void change_offset(float pan_x, float pan_y);
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
	void pan(float pan_x, float pan_y);
	~renderer();
};

