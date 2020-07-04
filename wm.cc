#include "wm.h"
#include "util.h"

void wm::init()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	_window = glfwCreateWindow(1280, 960, "pwpw", nullptr, nullptr);
	die_if(_window == nullptr);

	glfwMakeContextCurrent(_window);
}

bool wm::should_close()
{
	return glfwWindowShouldClose(_window);
}

void wm::poll_events()
{
	glfwPollEvents();
}

void wm::swap_window()
{
	glfwSwapBuffers(_window);
}

bool wm::key_down(key k)
{
	return glfwGetKey(_window, k) == GLFW_PRESS;
}

wm::~wm()
{
	glfwTerminate();
}

