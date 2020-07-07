#pragma once

#include <glm/mat4x4.hpp>

using glm::mat4;

class camera
{
	float offset_x;
	float offset_y;
	float scale;

	void calculate_viewmat();
public:
	mat4 view;

	camera();
	void change_scale(float diff);
	void change_offset(float pan_x, float pan_y);
};


