#pragma once

#include <GL/glew.h>

class vao
{
	GLuint id;
public:
	void create();
	void bind();
	~vao();
};

