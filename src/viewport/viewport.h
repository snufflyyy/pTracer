#pragma once

#include "math/vec2/vec2.h"

typedef struct Viewport {
	vec2 size;
	vec2 delta;
	vec2 first_pixel;
} Viewport;

Viewport viewport_create(u32 framebuffer_width, u32 framebuffer_height);
