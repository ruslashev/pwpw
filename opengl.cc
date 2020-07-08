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

void buffer::create(GLuint _type)
{
	type = _type;
	glGenBuffers(1, &id);
}

void buffer::bind()
{
	glBindBuffer(type, id);
}

void buffer::push_data(size_t size, const void * const data)
{
	bind();
	glBufferData(type, size, data, GL_STATIC_DRAW);
}

void buffer::stream_data(size_t size, const void * const data)
{
	bind();
	glBufferData(type, size, data, GL_STREAM_DRAW);
}

buffer::~buffer()
{
	glDeleteBuffers(1, &id);
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

	if (status != GL_TRUE) {
		glDeleteShader(id);
		die("failed to compile " << typestr << " shader");
	}
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

	if (status != GL_TRUE) {
		glDeleteProgram(id);
		die("failed to compile shader program");
	}
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

	glDetachShader(id, vert.id);
	glDetachShader(id, frag.id);

	bind();
}

void shprog::bind()
{
	glUseProgram(id);
}

int shprog::vertex_attrib(strlit name, int dim, size_t stride, void *offset)
{
	GLint attrib_id = glGetAttribLocation(id, name);

	glEnableVertexAttribArray(attrib_id);
	glVertexAttribPointer(attrib_id, dim, GL_FLOAT, GL_FALSE, stride, offset);

	return attrib_id;
}

int shprog::int_vertex_attrib(strlit name, int dim, GLenum type, size_t stride, void *offset)
{
	GLint attrib_id = glGetAttribLocation(id, name);

	glEnableVertexAttribArray(attrib_id);
	glVertexAttribIPointer(attrib_id, dim, type, stride, offset);

	return attrib_id;
}

int shprog::create_uniform(strlit name)
{
	return glGetUniformLocation(id, name);
}

shprog::~shprog()
{
	glDeleteProgram(id);
}

static const char* gl_message_type(GLenum type)
{
	switch (type) {
	case GL_DEBUG_TYPE_ERROR:               return "error";
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "deprecated_behavior";
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  return "undefined_behavior";
	case GL_DEBUG_TYPE_PORTABILITY:         return "portability";
	case GL_DEBUG_TYPE_PERFORMANCE:         return "performance";
	case GL_DEBUG_TYPE_OTHER:               return "other";
	case GL_DEBUG_TYPE_MARKER:              return "marker";
	case GL_DEBUG_TYPE_PUSH_GROUP:          return "push_group";
	case GL_DEBUG_TYPE_POP_GROUP:           return "pop_group";
	default:                                return "unknown";
	}
}

static const char* gl_message_severity(GLenum severity)
{
	switch (severity) {
	case GL_DEBUG_SEVERITY_HIGH:         return "high";
	case GL_DEBUG_SEVERITY_MEDIUM:       return "medium";
	case GL_DEBUG_SEVERITY_LOW:          return "low";
	case GL_DEBUG_SEVERITY_NOTIFICATION: return "notification";
	default:                             return "unknown";
	}
}

static const char* gl_message_source(GLenum source)
{
	switch (source) {
	case GL_DEBUG_SOURCE_API:             return "api";
	case GL_DEBUG_SOURCE_APPLICATION:     return "application";
	case GL_DEBUG_SOURCE_OTHER:           return "other";
	case GL_DEBUG_SOURCE_SHADER_COMPILER: return "shader_compiler";
	case GL_DEBUG_SOURCE_THIRD_PARTY:     return "third_party";
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   return "window_system";
	default:                              return "unknown";
	}
}

void gl_message_cb(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
		const GLchar *message, const void *userdata)
{
	if (source == GL_DEBUG_SOURCE_SHADER_COMPILER && severity == GL_DEBUG_SEVERITY_NOTIFICATION)
		return;

	std::cerr << "[GL"
	          << " " << gl_message_type(type)
	          << " " << gl_message_severity(severity)
	          << " " << gl_message_source(source)
	          << "]: " << message << std::endl;
}

