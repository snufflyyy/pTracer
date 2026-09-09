#include "viewport.h"
#include <math.h>

#include "math/angle/angle.h"

Viewport viewport_create(u32 framebuffer_width, u32 framebuffer_height, f32 fov) {
	Viewport viewport = {0};

	f32 height = 2.0f * tanf(angle_deg_to_rad(fov) / 2.0f);

	viewport.size = (vec2) { height * ((f32) framebuffer_width / (f32) framebuffer_height), height };
	viewport.delta = (vec2) { viewport.size.x / (f32) framebuffer_width, -(viewport.size.y / (f32) framebuffer_height) };
	viewport.first_pixel = (vec2) { -(viewport.size.x / 2.0f) + (0.5f * viewport.delta.x), (viewport.size.y / 2.0f) + (0.5f * viewport.delta.y) };

	return viewport;
}
