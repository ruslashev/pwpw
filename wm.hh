#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "keys.hh"

class wm
{
	GLFWwindow *_window;
public:
	wm();
	void init(int w, int h, void *event_cb_userdata);
	bool should_close();
	void poll_events();
	void swap_window();
	bool key_down(key k);
	bool mouse_key_down(mouse_key mk);
	bool mouse_key_up(mouse_key mk);
	void get_mouse_pos(float *x, float *y);
	double get_time();
	void set_title(const char *title);
	~wm();
};

