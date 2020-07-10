#pragma once

#include "opengl.hh"
#include "simulation.hh"

class renderer
{
	vao va;

	buffer ship_vertices;
	buffer ship_elements;
	buffer ship_instances;

	shprog shp;

	int uni_proj_id;
	int uni_view_id;
public:
	int w;
	int h;

	void init(int _w, int _h);
	void render(const state *s);
	void update_camera_mat(const float *view);
	~renderer();
};

