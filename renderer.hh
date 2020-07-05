#pragma once

#include "opengl.hh"

class renderer
{
	vao va;
	buffer vertices;
	buffer elements;
	buffer instances;
	shprog shp;

public:
	void init(int w, int h);
	void render();
	~renderer();
};

