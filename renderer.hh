#pragma once

#include "opengl.hh"
#include "simulation.hh"

class renderer
{
	vao va;
	buffer vertices;
	buffer elements;
	buffer instances;
	shprog shp;

	int uni_proj_id;
	int uni_view_id;
public:
	void init(int w, int h);
	void render(const state *s);
	void update_camera_mat(const float *view);
	~renderer();
};

