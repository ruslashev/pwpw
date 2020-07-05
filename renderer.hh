#pragma once

#include "opengl.hh"

class renderer
{
	vao va;
	shprog shp;

public:
	void init(int w, int h);
	void render();
	~renderer();
};

