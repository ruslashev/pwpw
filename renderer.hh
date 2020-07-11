#pragma once

#include "opengl.hh"
#include "simulation.hh"

class renderer
{
	vao ship_va;
	buffer ship_vertices;
	buffer ship_elements;
	buffer ship_instances;

	vao bullet_va;
	buffer bullet_vertices;
	buffer bullet_elements;
	buffer bullet_instances;

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

