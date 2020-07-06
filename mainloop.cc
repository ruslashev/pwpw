#include "mainloop.hh"
#include <cstdlib>
#include <cstdio>
#include <chrono>
#include <thread>

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

	w.mb_cb = mouse_button_cb;
}

void mainloop::mouse_button_cb(mouse_key k, action a)
{
	printf("mouse button event %d %d\n", k, a);
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

void mainloop::show_fps(float elapsed, uint64_t frames, float current)
{
	char title[100];

	snprintf(title, sizeof(title), "pwpw avg fps %.1f inst fps %.1f dt %.2f ms",
			(double)(frames / current),
			(double)(1.f / elapsed),
			(double)(elapsed * 1000.f));

	w.set_title(title);
}

void mainloop::run()
{
	init();

	const int tickrate = 50;
	const float dt = 1.f / (float)tickrate;
	const float max_frametime = 0.2f;
	const float max_fps = 500.f;
	const float min_frametime = 1.f / max_fps;
	float t = 0;

	float previous = w.get_time();
	float accumulator = 0;

	done = false;

	uint64_t frames = 0;

	while (!done) {
		const float current = w.get_time();
		float elapsed = current - previous;

		show_fps(elapsed, frames, current);

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

		frames++;

		w.swap_window();

		const float frametime = (float)w.get_time() - current;

		if (frametime < min_frametime) {
			const uint64_t to_sleep = (min_frametime - frametime) * 1000.f * 1000.f * 1000.f;
			std::this_thread::sleep_for(std::chrono::nanoseconds(to_sleep));
		}
	}
}

