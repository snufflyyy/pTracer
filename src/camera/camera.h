#pragma once

#include "base-types.h"
#include "color/color.h"
#include "math/vec3/vec3.h"
#include "viewport/viewport.h"
#include "world/world.h"

typedef struct Camera {
	Color* framebuffer;
	usize framebuffer_length;

	u32 framebuffer_width;
	u32 framebuffer_height;

	vec3 position;
	f32 focal_length;

	Viewport viewport;
} Camera;

Camera* camera_create(u32 framebuffer_width, u32 framebuffer_height);
void camera_render(Camera* camera, World* world);
void camera_destroy(Camera* camera);
