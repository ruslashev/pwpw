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

class shprog
{
	shader vert;
	shader frag;
public:
	GLuint id;

	void create(const char * const vsh, const char * const fsh);
	void bind();
	~shprog();
};

