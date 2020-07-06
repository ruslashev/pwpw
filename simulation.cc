#include "simulation.hh"

#include <glm/gtx/compatibility.hpp>

static void interpolate_ships(const ship &s1, const ship &s2, double t, ship *out)
{
	out->position = glm::lerp(s1.position, s2.position, (float)t);
	out->angle =    glm::lerp(s1.angle,    s2.angle,    (float)t);
}

void interpolate_states(const state &s1, const state &s2, double t, state *out)
{
	/* not accounting for removed ships */

	size_t n = s1.ships.size();

	out->ships.resize(n);

	for (size_t i = 0; i < n; ++i)
		interpolate_ships(s1.ships[i], s2.ships[i], t, &out->ships[i]);
}

