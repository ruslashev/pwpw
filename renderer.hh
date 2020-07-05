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

public:
	void init(int w, int h);
	void render(const state *s);
	~renderer();
};

