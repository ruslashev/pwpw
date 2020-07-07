#include "camera.hh"

#include <glm/gtc/matrix_transform.hpp>

void camera::calculate_viewmat()
{
	view = glm::translate(mat4(1), glm::vec3(offset_x, offset_y, 0.f));
	view = glm::scale(view, glm::vec3(scale, scale, 1.f));
}

camera::camera()
	: offset_x(0.f)
	, offset_y(0.f)
	, scale(1.f)
	, view(mat4(1))
{
}

void camera::change_scale(float diff)
{
	scale += scale * diff;
	calculate_viewmat();
}

void camera::change_offset(float pan_x, float pan_y)
{
	offset_x += pan_x;
	offset_y += pan_y;
	calculate_viewmat();
}

