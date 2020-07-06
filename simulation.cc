#include "simulation.hh"

#include <glm/gtx/compatibility.hpp>

static void interpolate_entities(const entity &s1, const entity &s2, double t, entity *out)
{
	out->position = glm::lerp(s1.position, s2.position, (float)t);
	out->angle =    glm::lerp(s1.angle,    s2.angle,    (float)t);
}

void interpolate_states(const state &s1, const state &s2, double t, state *out)
{
	/* not accounting for removed entities */

	size_t n = s1.entities.size();

	out->entities.resize(n);

	for (size_t i = 0; i < n; ++i)
		interpolate_entities(s1.entities[i], s2.entities[i], t, &out->entities[i]);
}

void state::update(double t, double dt)
{
	for (size_t i = 0; i < entities.size(); ++i)
		entities[i].angle += 5.f * (float)dt;
}

