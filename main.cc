#include "wm.hh"

int main()
{
	wm w;

	w.init();

	bool done = false;

	while (!done) {
		w.poll_events();

		if (w.key_down(KEY_ESC))
			done = true;

		done |= w.should_close();

		w.swap_window();
	}
}
