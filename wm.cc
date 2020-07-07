#include "wm.hh"
#include "util.hh"
#include "mainloop.hh"

static void center_window(GLFWwindow *window, int w, int h, GLFWmonitor *monitor)
{
	const GLFWvidmode *mode = glfwGetVideoMode(monitor);
	if (!mode)
		return;

	glfwSetWindowPos(window, (mode->width - w) / 2, (mode->height - h) / 2);
}

static void mouse_button_cb(GLFWwindow *window, int button, int maction, int mods)
{
	mainloop *m = (mainloop*)glfwGetWindowUserPointer(window);
	m->mouse_button_cb((mouse_key)button, (action)maction);
}

static void mouse_move_cb(GLFWwindow* window, double x, double y)
{
	mainloop *m = (mainloop*)glfwGetWindowUserPointer(window);
	m->mouse_move_cb((float)x, (float)y);
}

static void mouse_scroll_cb(GLFWwindow* window, double x, double y)
{
	mainloop *m = (mainloop*)glfwGetWindowUserPointer(window);
	m->mouse_scroll_cb((float)x, (float)y);
}

wm::wm() : _window(nullptr)
{
}

void wm::init(int w, int h, void *event_cb_userdata)
{
	die_if(!glfwInit());

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	_window = glfwCreateWindow(w, h, "pwpw", nullptr, nullptr);
	die_if(_window == nullptr);

	glfwSetWindowUserPointer(_window, event_cb_userdata);
	glfwSetMouseButtonCallback(_window, mouse_button_cb);
	glfwSetCursorPosCallback(_window, mouse_move_cb);
	glfwSetScrollCallback(_window, mouse_scroll_cb);

	center_window(_window, w, h, glfwGetPrimaryMonitor());

	glfwMakeContextCurrent(_window);

	glfwSwapInterval(0);
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

void wm::set_title(const char *title)
{
	glfwSetWindowTitle(_window, title);
}

wm::~wm()
{
	glfwDestroyWindow(_window);
	glfwTerminate();
}

