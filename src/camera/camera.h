#pragma once

#include "base-types.h"
#include "math/vec3/vec3.h"
#include "viewport/viewport.h"
#include "world/world.h"
#include "framebuffer/framebuffer.h"

typedef struct Camera {
	u32 sample_count;

	vec3 position;
	f32 focal_length;

	Viewport viewport;
} Camera;

Camera* camera_create(u32 framebuffer_width, u32 framebuffer_height);
void camera_render(Camera* camera, Framebuffer* framebuffer, World* world);
void camera_destroy(Camera* camera);
