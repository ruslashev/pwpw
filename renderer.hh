#pragma once

#include "opengl.hh"

class renderer
{
	vao va;

public:
	void init(int w, int h);
	void render();
	~renderer();
};

