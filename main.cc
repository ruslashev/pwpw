#include "wm.hh"
#include "renderer.hh"
#include "simulation.hh"
#include <cstdlib>

static void add_ships(state *s)
{
	for (int y = 0; y < 10; ++y)
		for (int x = 0; x < 10; ++x) {
			ship sh = {
				{ x * 100, y * 100 },
				(float)(rand() % 360)
			};
			s->ships.push_back(sh);
		}
}

int main()
{
	wm w;
	renderer r;
	state s;

	const int winw = 1280, winh = (winw * 3) / 4;

	w.init(winw, winh);
	r.init(winw, winh);

	add_ships(&s);

	const int tickrate = 50;
	const double dt = 1. / (double)tickrate;
	const double max_frametime = 0.2;
	double t = 0;

	double previous = w.get_time();
	double accumulator = 0;

	state prev_state;
	state current_state;

	add_ships(&current_state);

	bool done = false;

	while (!done) {
		double current = w.get_time();
		double elapsed = current - previous;

		if (elapsed > max_frametime)
			elapsed = max_frametime;

		previous = current;

		accumulator += elapsed;

		while (accumulator >= dt) {
			w.poll_events();

			if (w.key_down(KEY_ESC))
				done = true;

			prev_state = current_state;
			// update(&current_state, t, dt);
			t += dt;
			accumulator -= dt;
		}

		const double alpha = accumulator / dt;
		state draw_state;
		interpolate_states(prev_state, current_state, alpha, &draw_state);

		r.render(&draw_state);

		done |= w.should_close();

		w.swap_window();
	}
}
