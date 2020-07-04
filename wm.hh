#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "keys.hh"

class wm
{
	GLFWwindow *_window;

public:
	void init();
	bool should_close();
	void poll_events();
	void swap_window();
	bool key_down(key k);
	~wm();
};

