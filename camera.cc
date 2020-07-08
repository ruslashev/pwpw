#include "camera.hh"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void camera::calculate_viewmat()
{
	mat4 view = mat4(1);

	view = glm::translate(view, glm::vec3(offset_x, offset_y, 0.f));

	view = glm::translate(view, glm::vec3((float)r->w / 2.f, (float)r->h / 2.f, 0.f));
	view = glm::scale(view, glm::vec3(scale, scale, 1.f));
	view = glm::translate(view, glm::vec3(-(float)r->w / 2.f, -(float)r->h / 2.f, 0.f));

	r->update_camera_mat(glm::value_ptr(view));
}

void camera::init(renderer *_r)
{
	offset_x = 0.f;
	offset_y = 0.f;
	scale = 1.f;
	needs_commit = true;
	r = _r;
}

void camera::change_scale(float diff)
{
	scale += scale * diff;
	needs_commit = true;
}

void camera::change_offset(float pan_x, float pan_y)
{
	offset_x += pan_x;
	offset_y += pan_y;
	needs_commit = true;
}

void camera::commit_matrix()
{
	if (!needs_commit)
		return;

	calculate_viewmat();
	needs_commit = false;
}

