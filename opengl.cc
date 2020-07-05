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

void shprog::check_link_status()
{
	GLint status;
	glGetProgramiv(id, GL_LINK_STATUS, &status);

	GLint loglen;
	glGetProgramiv(id, GL_INFO_LOG_LENGTH, &loglen);

	if (loglen != 0) {
		char *infolog = new char[loglen];
		glGetProgramInfoLog(id, loglen, NULL, infolog);

		std::cout << "shader program info log:" << std::endl;
		std::cout << infolog;

		delete [] infolog;
	}

	if (status != GL_TRUE)
		die("failed to compile shader program");
}

void shprog::create(const char * const vsh, const char * const fsh)
{
	vert.create(GL_VERTEX_SHADER, vsh);
	frag.create(GL_FRAGMENT_SHADER, fsh);

	id = glCreateProgram();

	glAttachShader(id, vert.id);
	glAttachShader(id, frag.id);

	glLinkProgram(id);

	check_link_status();

	bind();
}

void shprog::bind()
{
	glUseProgram(id);
}

shprog::~shprog()
{
	glDeleteProgram(id);
}

