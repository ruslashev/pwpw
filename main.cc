#include "wm.hh"
#include "renderer.hh"

int main()
{
	wm w;
	renderer r;
	const int winw = 1280, winh = (winw * 3) / 4;

	w.init(winw, winh);
	r.init(winw, winh);

	const int tickrate = 50;
	const double dt = 1. / (double)tickrate;

	double previous = w.get_time();
	double lag = 0.0;

	bool done = false;

	while (!done) {
		double current = w.get_time();
		double elapsed = current - previous;

		previous = current;
		lag += elapsed;

		while (lag >= dt) {
			w.poll_events();

			if (w.key_down(KEY_ESC))
				done = true;

			// update();

			lag -= dt;
		}

		r.render();

		done |= w.should_close();

		w.swap_window();
	}
}
