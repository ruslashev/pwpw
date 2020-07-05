#pragma once

#include "opengl.hh"

class renderer
{
	vao va;
	shader vert;
	shader frag;

public:
	void init(int w, int h);
	void render();
	~renderer();
};

