#include "mainloop.hh"
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

void mainloop::init()
{
	const int winw = 1280, winh = (winw * 3) / 4;

	w.init(winw, winh);
	r.init(winw, winh);

	add_entities(&current_state);
}

void mainloop::poll_events()
{
	w.poll_events();

	if (w.key_down(KEY_ESC))
		done = true;
}

void mainloop::update(float t, float dt)
{
	current_state.update(t, dt);
}

void mainloop::draw(float alpha)
{
	state draw_state;
	interpolate_states(prev_state, current_state, alpha, &draw_state);

	r.render(&draw_state);
}

void mainloop::run()
{
	init();

	const int tickrate = 50;
	const float dt = 1.f / (float)tickrate;
	const float max_frametime = 0.2;
	float t = 0;

	float previous = w.get_time();
	float accumulator = 0;

	done = false;

	while (!done) {
		float current = w.get_time();
		float elapsed = current - previous;

		if (elapsed > max_frametime)
			elapsed = max_frametime;

		previous = current;

		accumulator += elapsed;

		while (accumulator >= dt) {
			poll_events();

			prev_state = current_state;
			update(t, dt);
			t += dt;
			accumulator -= dt;
		}

		draw(accumulator / dt);

		done |= w.should_close();

		w.swap_window();
	}
}

