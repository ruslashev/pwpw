#pragma once

#include "wm.hh"
#include "renderer.hh"
#include "simulation.hh"

class mainloop
{
	wm w;
	renderer r;

	state prev_state;
	state current_state;

	bool done;

	void init();
	void poll_events();
	void update(float t, float dt);
	void draw(float alpha);

	static void mouse_button_cb(mouse_key k, action a);
	static void mouse_move_cb(float x, float y);
	static void mouse_scroll_cb(float x, float y);

	void show_fps(float elapsed, uint64_t frames, float current);
public:
	void run();
};

