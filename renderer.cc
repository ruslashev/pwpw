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

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(gl_message_cb, nullptr);

	va.create();

	float vertices_data[] = {
		25.f, 50.f,
		50.f, 0.f,
		0.f,  0.f
	};

	vertices.create(GL_ARRAY_BUFFER);
	vertices.push_data(sizeof(vertices_data), vertices_data);

	GLuint elements_data[] = {
		0, 1, 2
	};

	elements.create(GL_ELEMENT_ARRAY_BUFFER);
	elements.push_data(sizeof(elements_data), elements_data);

	float translations[2 * 100];
	int index = 0;
	for (int y = 0; y < 10; ++y)
		for (int x = 0; x < 10; ++x) {
			translations[index++] = x * 100;
			translations[index++] = y * 100;
		}

	instances.create(GL_ARRAY_BUFFER);
	instances.push_data(sizeof(translations), translations);

	strlit vsh = R"(
		#version 150 core

		in vec2 position;
		in vec2 inst_offset;

		uniform mat4 proj;

		void main()
		{
			gl_Position = proj * vec4(position + inst_offset, 0.0, 1.0);
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

	vertices.bind();
	shp.vertex_attrib("position", 2, 0, 0);

	instances.bind();
	int inst_offset_attrib_id = shp.vertex_attrib("inst_offset", 2, 0, 0);
	glVertexAttribDivisor(inst_offset_attrib_id, 1);

	glm::mat4 proj = glm::ortho(0.f, (float)w, (float)h, 0.f, 0.f, 1.f);
	int uni_proj_id = shp.create_uniform("proj");
	glUniformMatrix4fv(uni_proj_id, 1, GL_FALSE, glm::value_ptr(proj));
}

void renderer::render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawElementsInstanced(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0, 100);
}

renderer::~renderer()
{
}

