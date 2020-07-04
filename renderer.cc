#define GLEW_STATIC
#include <GL/glew.h>

#include "renderer.hh"
#include <iostream>

void renderer::init()
{
	glewExperimental = GL_TRUE;
	glewInit();

	float vertices[] = {
		 0.0f,  0.5f,
		 0.5f, -0.5f,
		-0.5f, -0.5f
	};

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	const char * const vsh = R"(
		#version 150 core

		in vec2 position;

		void main()
		{
			gl_Position = vec4(position, 0.0, 1.0);
		}
	)";

	const char * const fsh = R"(
		#version 150 core

		out vec4 out_color;

		void main()
		{
			out_color = vec4(1.0, 1.0, 1.0, 1.0);
		}
	)";

	GLuint vsh_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vsh_id, 1, &vsh, NULL);
	glCompileShader(vsh_id);

	GLuint fsh_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsh_id, 1, &fsh, NULL);
	glCompileShader(fsh_id);

	GLuint shprog_id = glCreateProgram();
	glAttachShader(shprog_id, vsh_id);
	glAttachShader(shprog_id, vsh_id);

	glBindFragDataLocation(shprog_id, 0, "out_color");

	glLinkProgram(shprog_id);

	glUseProgram(shprog_id);

	GLint pos_attrib_id = glGetAttribLocation(shprog_id, "position");
	glVertexAttribPointer(pos_attrib_id, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(pos_attrib_id);
}

void renderer::render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

renderer::~renderer()
{
}

