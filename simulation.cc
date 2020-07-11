#include "simulation.hh"

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

void entity::update(float t, float dt)
{
	float old_vel_x = vel_x;
	float old_vel_y = vel_y;

	vel_x = vel_x + acc_x * dt;
	vel_y = vel_y + acc_y * dt;

	x = x + (old_vel_x + vel_x) * 0.5f * dt;
	y = y + (old_vel_y + vel_y) * 0.5f * dt;
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

	for (int y = 0; y < 5; ++y)
		for (int x = 0; x < 5; ++x) {
			entity sh = {
				x * 200.f,
				y * 200.f,
				(float)(rand() % 360),
				(uint8_t)(rand() % 4),
				0, 0,
				0, 0,
			};
			s->entities.push_back(sh);

			sh.acc_x = 5.f * cosf(sh.angle);
			sh.acc_y = 5.f * sinf(sh.angle);
			s->bullets.push_back(sh);
		}
}

void simulation::init()
{
	add_entities(&current);
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

