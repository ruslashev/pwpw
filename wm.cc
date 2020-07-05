#include "wm.hh"
#include "util.hh"

static void center_window(GLFWwindow *window, int w, int h, GLFWmonitor *monitor)
{
	const GLFWvidmode *mode = glfwGetVideoMode(monitor);
	if (!mode)
		return;

	glfwSetWindowPos(window, (mode->width - w) / 2, (mode->height - h) / 2);
}

void wm::init(int w, int h)
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	_window = glfwCreateWindow(w, h, "pwpw", nullptr, nullptr);
	die_if(_window == nullptr);

	center_window(_window, w, h, glfwGetPrimaryMonitor());

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

double wm::get_time()
{
	return glfwGetTime();
}

wm::~wm()
{
	glfwDestroyWindow(_window);
	glfwTerminate();
}

