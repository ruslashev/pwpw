#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "keys.hh"

typedef void (*mouse_button_cb_t)(mouse_key, action);
typedef void (*mouse_move_cb_t)(float, float);

class wm
{
	GLFWwindow *_window;
public:
	mouse_button_cb_t mb_cb;
	mouse_move_cb_t m_cb;

	wm();
	void init(int w, int h);
	bool should_close();
	void poll_events();
	void swap_window();
	bool key_down(key k);
	double get_time();
	void set_title(const char *title);
	~wm();
};

