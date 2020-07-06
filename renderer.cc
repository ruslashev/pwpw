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

	instances.create(GL_ARRAY_BUFFER);

	strlit vsh = R"(
		#version 150 core

		in vec2 position;
		in vec3 inst_data;

		uniform mat4 proj;

		mat4 translate(vec2 pos)
		{
			return mat4(1,     0,     0, 0,
			            0,     1,     0, 0,
			            0,     0,     1, 0,
			            pos.x, pos.y, 0, 1);
		}

		mat4 rotate(float ang)
		{
			return mat4(cos(ang), -sin(ang), 0, 0,
			            sin(ang),  cos(ang), 0, 0,
			            0,         0,        1, 0,
			            0,         0,        0, 1);
		}

		void main()
		{
			gl_Position = proj *
				translate(inst_data.xy) *
				translate(vec2(25, 25)) *
				rotate(inst_data.z) *
				translate(vec2(-25, -25)) *
				vec4(position, 0.0, 1.0);
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
	int inst_data_attrib_id = shp.vertex_attrib("inst_data", 3, 0, 0);
	glVertexAttribDivisor(inst_data_attrib_id, 1);

	glm::mat4 proj = glm::ortho(0.f, (float)w, (float)h, 0.f, 0.f, 1.f);
	int uni_proj_id = shp.create_uniform("proj");
	glUniformMatrix4fv(uni_proj_id, 1, GL_FALSE, glm::value_ptr(proj));
}

void renderer::render(const state *s)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	size_t nentities = s->entities.size();
	std::vector<float> instances_data;
	instances_data.resize(3 * nentities);
	int idx = 0;
	for (size_t i = 0; i < nentities; ++i) {
		instances_data[idx++] = s->entities[i].position.x;
		instances_data[idx++] = s->entities[i].position.y;
		instances_data[idx++] = s->entities[i].angle;
	}

	instances.bind();
	instances.stream_data(instances_data.size() * sizeof(instances_data[0]), instances_data.data());

	glDrawElementsInstanced(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0, nentities);
}

renderer::~renderer()
{
}

