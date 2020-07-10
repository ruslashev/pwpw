#pragma once

static const float ship_vertices_data[] = {
	 22.f,   0.f,
	 -8.f,   0.f,
	-14.f,  18.f,
	-14.f, -18.f,
};

#define ship_numelements 6

static const unsigned int ship_elements_data[] = {
	0, 2, 1,
	0, 1, 3,
};

#define bthick  4.5f
#define blong   17.f
#define bschnoz 1.6f
#define bthickh bthick / 2.f
#define blongh  blong / 2.f

static const float bullet_vertices_data[] = {
	 blongh,            bthickh,
	 blongh + bschnoz,      0.f,
	 blongh,           -bthickh,
	-blongh,            bthickh,
	-blongh - bschnoz,      0.f,
	-blongh,           -bthickh,
};

#define bullet_numelements 12

static const unsigned int bullet_elements_data[] = {
	0, 2, 1,
	0, 3, 2,
	3, 5, 2,
	3, 5, 4,
};

struct rgb
{
	float r, g, b;
};

static constexpr rgb _hsv2rgb(float h, float s, float v)
{
	while (h >= 1.f)
		h -= 1.f;

	h *= 6;

	int I = h;
	float F = h - I;

	float M = v * (1 - s);
	float N = v * (1 - s * F);
	float K = v * (1 - s * (1 - F));

	if (I == 0) return { v, K, M };
	if (I == 1) return { N, v, M };
	if (I == 2) return { M, v, K };
	if (I == 3) return { M, N, v };
	if (I == 4) return { K, M, v };
	if (I == 5) return { v, M, N };
}

#define hsv2rgb(H, S, V) \
	_hsv2rgb(H, S, V).r, _hsv2rgb(H, S, V).g, _hsv2rgb(H, S, V).b

#define MAX_TEAMS 4
static constexpr float team_colors[3 * MAX_TEAMS] = {
	hsv2rgb(0,     0.8,  0.95),
	hsv2rgb(0.625, 0.8,  0.95),
	hsv2rgb(0.25,  0.8,  0.95),
	hsv2rgb(0.875, 0.75, 0.95),
	                       // /* h,     s,    v   */
	// 0.9f,  0.18f,  0.18f,  /* 0,     0.8,  0.9 */
	// 0.18f, 0.36f,  0.9f,   /* 0.625, 0.8,  0.9 */
	// 0.54f, 0.9f,   0.18f,  /* 0.25,  0.8,  0.9 */
	// 0.9f , 0.225f, 0.731f, /* 0.875, 0.75, 0.9 */
};

