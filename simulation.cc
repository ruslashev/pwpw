#include "simulation.hh"

#include <glm/gtx/compatibility.hpp>

static void interpolate_entities(const entity &s1, const entity &s2, float t, entity *out)
{
	out->x     = glm::lerp(s1.x,     s2.x,     t);
	out->y     = glm::lerp(s1.y,     s2.y,     t);
	out->angle = glm::lerp(s1.angle, s2.angle, t);
	out->team  = s2.team;
}

static void interpolate_states(const state &s1, const state &s2, float t, state *out)
{
	/* not accounting for removed entities */

	size_t n = s1.entities.size();

	out->entities.resize(n);

	for (size_t i = 0; i < n; ++i)
		interpolate_entities(s1.entities[i], s2.entities[i], t, &out->entities[i]);
}

void entity::update(float t, float dt)
{
	// angle += 5.f * dt;

	vel_x = vel_x + acc_x * dt;
	vel_y = vel_y + acc_y * dt;

	x = x + vel_x * dt;
	y = y + vel_y * dt;
}

void state::update(float t, float dt)
{
	for (size_t i = 0; i < entities.size(); ++i)
		entities[i].update(t, dt);
}

static void add_entities(state *s)
{
	srand(1);

	for (int y = 0; y < 10; ++y)
		for (int x = 0; x < 10; ++x) {
			entity sh = {
				x * 100.f,
				y * 100.f,
				(float)(rand() % 360),
				(uint8_t)(rand() % 4),
				0, 0,
				0, 0,
			};
			sh.acc_x = 5.f * cosf(sh.angle);
			sh.acc_y = 5.f * sinf(sh.angle);
			s->entities.push_back(sh);
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
	interpolate_states(previous, current, alpha, s);
}

