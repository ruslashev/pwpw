#pragma once

#include "opengl.hh"
#include "simulation.hh"
#include "camera.hh"

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

