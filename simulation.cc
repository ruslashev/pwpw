#include "simulation.hh"
#include "macros.hh"
#include "config.hh"
#include <glm/gtx/compatibility.hpp>

static void interpolate_entities(const entity &e1, const entity &e2, float t, entity *out)
{
	out->x     = glm::lerp(e1.x,     e2.x,     t);
	out->y     = glm::lerp(e1.y,     e2.y,     t);
	out->angle = glm::lerp(e1.angle, e2.angle, t);
	out->team  = e2.team;
}

static void interpolate_entity_lists(const entlist &s1, const entlist &s2, float t, entlist *out)
{
	/* not accounting for removed entities */

	size_t n = s1.size();

	out->resize(n);

	for (size_t i = 0; i < n; ++i)
		interpolate_entities(s1[i], s2[i], t, &(*out)[i]);
}

void entity::fire()
{
	float bullet_angle = angle;
	float bullet_vel_x = 50.f * cosf(bullet_angle);
	float bullet_vel_y = 50.f * sinf(bullet_angle);
	entity bullet = {
		x,
		y,
		angle,
		team,
		bullet_vel_x, bullet_vel_y,
		0, 0,
		0,
	};

	parent->bullets.push_back(bullet);
}

void entity::update(float t, float dt)
{
	float old_vel_x = vel_x;
	float old_vel_y = vel_y;

	vel_x += acc_x * dt;
	vel_y += acc_y * dt;

	x += (old_vel_x + vel_x) * 0.5f * dt;
	y += (old_vel_y + vel_y) * 0.5f * dt;
}

void state::update(float t, float dt)
{
	for (size_t i = 0; i < entities.size(); ++i)
		entities[i].update(t, dt);

	for (size_t i = 0; i < bullets.size(); ++i)
		bullets[i].update(t, dt);
}

static void add_entities(state *s)
{
	srand(1);

	int spawn_width = 200;
	int ships_in_team = 20;

	for (int i = 0; i < ships_in_team; ++i) {
		entity sh = {
			(float)(rand() % spawn_width),
			(float)(rand() % initial_winh),
			(float)(rand() % 360),
			0,
			0, 0,
			0, 0,
			s,
		};
		s->entities.push_back(sh);
	}

	for (int i = 0; i < ships_in_team; ++i) {
		entity sh = {
			(float)(initial_winw - spawn_width + (rand() % spawn_width)),
			(float)(rand() % initial_winh),
			(float)(rand() % 360),
			1,
			0, 0,
			0, 0,
			s,
		};
		s->entities.push_back(sh);
	}

}

void simulation::init()
{
	add_entities(&current);

	for (size_t i = 0; i < current.entities.size(); ++i)
		current.entities[i].fire();
}

void simulation::update(float t, float dt)
{
	previous = current;
	current.update(t, dt);
}

void simulation::get_draw_state(float alpha, state *s)
{
	interpolate_entity_lists(previous.entities, current.entities, alpha, &s->entities);
	interpolate_entity_lists(previous.bullets, current.bullets, alpha, &s->bullets);
}

