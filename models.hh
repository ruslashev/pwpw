#pragma once

static const float model_vertices[] = {
	 22.f,   0.f,
	 -8.f,   0.f,
	-14.f,  18.f,
	-14.f, -18.f,
};

static const unsigned int model_elements[] = {
	0, 2, 1,
	0, 1, 3,
};

#define MAX_TEAMS 4
static const float team_colors[3 * MAX_TEAMS] = {
	                       /* h,     s,    v   */
	0.9f,  0.18f,  0.18f,  /* 0,     0.8,  0.9 */
	0.18f, 0.36f,  0.9f,   /* 0.625, 0.8,  0.9 */
	0.54f, 0.9f,   0.18f,  /* 0.25,  0.8,  0.9 */
	0.9f , 0.225f, 0.731f, /* 0.875, 0.75, 0.9 */
};

