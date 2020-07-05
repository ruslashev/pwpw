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

		s.ships.clear();
		add_ships(&s);

		r.render(&s);

		done |= w.should_close();

		w.swap_window();
	}
}
