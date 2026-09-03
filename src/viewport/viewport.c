#include "viewport.h"

Viewport viewport_create(u32 framebuffer_width, u32 framebuffer_height) {
	Viewport viewport = {0};

	viewport.size = (vec2) { 4.0f * ((f32) framebuffer_width / (f32) framebuffer_height), 4.0f };
	viewport.pixel_delta = (vec2) { viewport.size.x / (f32) framebuffer_width, -(viewport.size.y / (f32) framebuffer_height) };
	viewport.first_pixel = (vec2) { -(viewport.size.x / 2.0f), viewport.size.y / 2.0f };

	return viewport;
}
