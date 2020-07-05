#define GLEW_STATIC
#include <GL/glew.h>

#include "renderer.hh"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void renderer::init(int w, int h)
{
	glewExperimental = GL_TRUE;
	glewInit();

	va.create();

	float vertices[] = {
		 0.0f,  0.5f,
		 0.5f, -0.5f,
		-0.5f, -0.5f
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint elements[] = {
		0, 1, 2
	};

	GLuint ebo;
	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	strlit vsh = R"(
		#version 150 core

		in vec2 position;

		uniform mat4 model;
		uniform mat4 view;
		uniform mat4 proj;

		void main()
		{
			gl_Position = proj * view * model * vec4(position, 0.0, 1.0);
		}
	)";

	strlit fsh = R"(
		#version 150 core

		out vec4 out_color;

		void main()
		{
			out_color = vec4(1.0, 1.0, 1.0, 1.0);
		}
	)";

	shp.create(vsh, fsh);

	shp.vertex_attrib("position", 2, 0, 0);

	glm::mat4 model = glm::mat4(1.0f);
	int uni_model_id = shp.create_uniform("model");
	glUniformMatrix4fv(uni_model_id, 1, GL_FALSE, glm::value_ptr(model));

	glm::mat4 view = glm::lookAt(glm::vec3(1.f, 1.f, 1.f),
	                             glm::vec3(0.f, 0.f, 0.f),
	                             glm::vec3(0.f, 0.f, 1.f));
	int uni_view_id  = shp.create_uniform("view");
	glUniformMatrix4fv(uni_view_id, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 proj = glm::perspective(glm::radians(60.0f), (float)w / (float)h, 0.1f, 10.0f);
	int uni_proj_id = shp.create_uniform("proj");
	glUniformMatrix4fv(uni_proj_id, 1, GL_FALSE, glm::value_ptr(proj));
}

void renderer::render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}

renderer::~renderer()
{
}

