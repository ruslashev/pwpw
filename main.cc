#include "wm.hh"
#include "renderer.hh"
#include "simulation.hh"
#include <cstdlib>

static void add_entities(state *s)
{
	for (int y = 0; y < 10; ++y)
		for (int x = 0; x < 10; ++x) {
			entity sh = {
				x * 100.f,
				y * 100.f,
				(float)(rand() % 360)
			};
			s->entities.push_back(sh);
		}
}

int main()
{
	wm w;
	renderer r;

	const int winw = 1280, winh = (winw * 3) / 4;

	w.init(winw, winh);
	r.init(winw, winh);

	const int tickrate = 50;
	const float dt = 1.f / (float)tickrate;
	const float max_frametime = 0.2;
	float t = 0;

	float previous = w.get_time();
	float accumulator = 0;

	state prev_state;
	state current_state;

	add_entities(&current_state);

	bool done = false;

	while (!done) {
		float current = w.get_time();
		float elapsed = current - previous;

		if (elapsed > max_frametime)
			elapsed = max_frametime;

		previous = current;

		accumulator += elapsed;

		while (accumulator >= dt) {
			w.poll_events();

			if (w.key_down(KEY_ESC))
				done = true;

			prev_state = current_state;
			current_state.update(t, dt);
			t += dt;
			accumulator -= dt;
		}

		const float alpha = accumulator / dt;
		state draw_state;
		interpolate_states(prev_state, current_state, alpha, &draw_state);

		r.render(&draw_state);

		done |= w.should_close();

		w.swap_window();
	}
}
