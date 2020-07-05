#include "opengl.hh"

void vao::create()
{
	glGenVertexArrays(1, &id);
	bind();
}

void vao::bind()
{
	glBindVertexArray(id);
}

vao::~vao()
{
	glDeleteVertexArrays(1, &id);
}

