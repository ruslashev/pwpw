#include "mainloop.hh"
#include <cstdlib>
#include <cstdio>
#include <chrono>
#include <thread>

void mainloop::init()
{
	const int winw = 1280, winh = (winw * 3) / 4;

	w.init(winw, winh, this);
	r.init(winw, winh);
	cam.init(&r);
	s.init();
}

void mainloop::poll_events()
{
	w.poll_events();

	if (w.key_down(KEY_ESC))
		done = true;

	if (w.mouse_key_down(MKEY_LEFT)) {
		float x, y;
		w.get_mouse_pos(&x, &y);

		if (!std::isnan(prev_pan_x))
			cam.change_offset(x - prev_pan_x, prev_pan_y - y);

		prev_pan_x = x;
		prev_pan_y = y;
	}
}

void mainloop::update(float t, float dt)
{
	s.update(t, dt);
}

void mainloop::draw(float alpha)
{
	state draw_state;

	s.get_draw_state(alpha, &draw_state);
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

mainloop::mainloop()
	: prev_pan_x(std::numeric_limits<float>::quiet_NaN())
	, prev_pan_y(prev_pan_x)
{
}

void mainloop::mouse_button_cb(mouse_key k, action a)
{
	if (k == MKEY_LEFT && a != ACTION_REPEAT)
		w.get_mouse_pos(&prev_pan_x , &prev_pan_y);
}

void mainloop::mouse_move_cb(float x, float y)
{
}

void mainloop::mouse_scroll_cb(float x, float y)
{
	cam.change_scale(y * 0.1f);
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

