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

void shader::create(GLuint type, strlit src)
{
	id = glCreateShader(type);

	glShaderSource(id, 1, &src, NULL);

	glCompileShader(id);

	GLint status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);

	GLint loglen;
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &loglen);

	strlit typestr = type == GL_VERTEX_SHADER ? "vertex" : "fragment";

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

void shprog::create(strlit vsh, strlit fsh)
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

void shprog::vertex_attrib(strlit name, int dim, size_t stride, void *offset)
{
	GLint attrib_id = glGetAttribLocation(id, name);
	glEnableVertexAttribArray(attrib_id);
	glVertexAttribPointer(attrib_id, dim, GL_FLOAT, GL_FALSE, stride, offset);
}

int shprog::create_uniform(strlit name)
{
	return glGetUniformLocation(id, name);
}

shprog::~shprog()
{
	glDeleteProgram(id);
}

