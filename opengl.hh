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

class shader
{
public:
	GLuint id;

	void create(GLuint type, const char * const src);
	~shader();
};

