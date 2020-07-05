#include "opengl.hh"
#include "util.hh"
#include <iostream>

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

void shader::create(GLuint type, const char * const src)
{
	id = glCreateShader(type);

	glShaderSource(id, 1, &src, NULL);

	glCompileShader(id);

	GLint status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);

	GLint loglen;
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &loglen);

	const char * const typestr = type == GL_VERTEX_SHADER ? "vertex" : "fragment";

	if (loglen != 0) {
		char *infolog = new char[loglen];
		glGetShaderInfoLog(id, loglen, NULL, infolog);

		std::cout << typestr << " shader info log:" << std::endl;
		std::cout << infolog;

		delete [] infolog;
	}

	if (status != GL_TRUE)
		die("failed to compile " << typestr << " shader");
}

shader::~shader()
{
	glDeleteShader(id);
}

