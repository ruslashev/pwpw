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
	GLuint id;

	shader vert;
	shader frag;

	void check_link_status();
public:
	void create(const char * const vsh, const char * const fsh);
	void bind();
	void vertex_attrib(const char * const name, int dim, size_t stride, void *offset);
	int create_uniform(const char * const name);
	~shprog();
};

