#pragma once

#include <GL/glew.h>
#include "macros.hh"

class vao
{
	GLuint id;
public:
	void create();
	void bind();
	~vao();
};

class buffer
{
	GLuint id;
	GLuint type;
public:
	void create(GLuint _type);
	void bind();
	void push_data(size_t size, const void * const data);
	~buffer();
};

class shader
{
public:
	GLuint id;

	void create(GLuint type, strlit src);
	~shader();
};

class shprog
{
	GLuint id;

	shader vert;
	shader frag;

	void check_link_status();
public:
	void create(strlit vsh, strlit fsh);
	void bind();
	int vertex_attrib(strlit name, int dim, size_t stride, void *offset);
	int create_uniform(strlit name);
	~shprog();
};

