#include <epoxy/gl.h>

#include "renderer.hh"
#include "models.hh"
#include "macros.hh"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void renderer::init(int _w, int _h)
{
	w = _w;
	h = _h;

	glEnable(GL_MULTISAMPLE);

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(gl_message_cb, nullptr);

	ship_va.create();
	ship_vertices.create(GL_ARRAY_BUFFER);
	ship_vertices.push_data(sizeof(ship_vertices_data), ship_vertices_data);
	ship_elements.create(GL_ELEMENT_ARRAY_BUFFER);
	ship_elements.push_data(sizeof(ship_elements_data), ship_elements_data);
	ship_instances.create(GL_ARRAY_BUFFER);

	bullet_va.create();
	bullet_vertices.create(GL_ARRAY_BUFFER);
	bullet_vertices.push_data(sizeof(bullet_vertices_data), bullet_vertices_data);
	bullet_elements.create(GL_ELEMENT_ARRAY_BUFFER);
	bullet_elements.push_data(sizeof(bullet_elements_data), bullet_elements_data);
	bullet_instances.create(GL_ARRAY_BUFFER);

	strlit vsh = R"(
		#version 150 core

		in vec2 position;
		in vec3 inst_data;
		in uint inst_team;

		out vec3 color;

		uniform mat4 proj;
		uniform mat4 view;
		uniform vec3 teams[)" strfy(MAX_TEAMS) R"(4];

		mat4 translate(vec2 pos)
		{
			return mat4(1,     0,     0, 0,
			            0,     1,     0, 0,
			            0,     0,     1, 0,
			            pos.x, pos.y, 0, 1);
		}

		mat4 rotate(float ang)
		{
			return mat4( cos(ang), sin(ang), 0, 0,
			            -sin(ang), cos(ang), 0, 0,
			             0,        0,        1, 0,
			             0,        0,        0, 1);
		}

		void main()
		{
			color = teams[inst_team];
			gl_Position = proj *
				view *
				translate(inst_data.xy) *
				rotate(inst_data.z) *
				vec4(position, 0.0, 1.0);
		}
	)";

	strlit fsh = R"(
		#version 150 core

		in vec3 color;

		out vec4 out_color;

		void main()
		{
			out_color = vec4(color, 1.0);
		}
	)";

	shp.create(vsh, fsh);

	ship_va.bind();
	ship_vertices.bind();
	shp.vertex_attrib("position", 2, 0, 0);
	ship_instances.bind();
	int inst_data_attrib_id = shp.vertex_attrib("inst_data", 3, sizeof(entity), 0);
	glVertexAttribDivisor(inst_data_attrib_id, 1);
	int inst_team_attrib_id = shp.int_vertex_attrib("inst_team", 1, GL_UNSIGNED_BYTE,
			sizeof(entity), (void*)(3 * sizeof(float)));
	glVertexAttribDivisor(inst_team_attrib_id, 1);

	bullet_va.bind();
	bullet_vertices.bind();
	shp.vertex_attrib("position", 2, 0, 0);
	bullet_instances.bind();
	inst_data_attrib_id = shp.vertex_attrib("inst_data", 3, sizeof(entity), 0);
	glVertexAttribDivisor(inst_data_attrib_id, 1);
	inst_team_attrib_id = shp.int_vertex_attrib("inst_team", 1, GL_UNSIGNED_BYTE,
			sizeof(entity), (void*)(3 * sizeof(float)));
	glVertexAttribDivisor(inst_team_attrib_id, 1);

	glm::mat4 proj = glm::ortho(0.f, (float)w, 0.f, (float)h, 0.f, 1.f);
	uni_proj_id = shp.create_uniform("proj");
	glUniformMatrix4fv(uni_proj_id, 1, GL_FALSE, glm::value_ptr(proj));

	uni_view_id = shp.create_uniform("view");
	glUniformMatrix4fv(uni_view_id, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.f)));

	int uni_teams_id = shp.create_uniform("teams");
	glUniform3fv(uni_teams_id, MAX_TEAMS, team_colors);
}

void renderer::render(const state *s)
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	ship_va.bind();
	ship_instances.bind();
	ship_instances.stream_data(s->entities.size() * sizeof(s->entities[0]), s->entities.data());

	glDrawElementsInstanced(GL_TRIANGLES, ship_numelements, GL_UNSIGNED_INT, 0, s->entities.size());

	bullet_va.bind();
	bullet_instances.bind();
	bullet_instances.stream_data(s->bullets.size() * sizeof(s->bullets[0]), s->bullets.data());

	glDrawElementsInstanced(GL_TRIANGLES, bullet_numelements, GL_UNSIGNED_INT, 0, s->bullets.size());
}

void renderer::update_camera_mat(const float *view)
{
	glUniformMatrix4fv(uni_view_id, 1, GL_FALSE, view);
}

renderer::~renderer()
{
}

