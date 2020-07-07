#pragma once

#include "renderer.hh"
#include <glm/mat4x4.hpp>

using glm::mat4;

class camera
{
	float offset_x;
	float offset_y;
	float scale;

	renderer *r;

	void calculate_viewmat();
public:
	void init(renderer *_r);
	void change_scale(float diff);
	void change_offset(float pan_x, float pan_y);
};


