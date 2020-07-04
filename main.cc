#include "wm.hh"
#include "renderer.hh"

int main()
{
	wm w;
	renderer r;

	w.init();
	r.init();

	bool done = false;

	while (!done) {
		w.poll_events();

		if (w.key_down(KEY_ESC))
			done = true;

		done |= w.should_close();

		r.render();

		w.swap_window();
	}
}
