#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "keys.hh"

class wm
{
	GLFWwindow *_window;

public:
	void init(int w, int h);
	bool should_close();
	void poll_events();
	void swap_window();
	bool key_down(key k);
	double get_time();
	void set_title(const char *title);
	~wm();
};

