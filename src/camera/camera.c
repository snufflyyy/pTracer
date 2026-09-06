#include "camera.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base-types.h"
#include "color/color.h"
#include "framebuffer/framebuffer.h"
#include "math/vec2/vec2.h"
#include "math/vec3/vec3.h"
#include "math/ray/ray.h"
#include "math/random/random.h"
#include "world/world.h"

Camera* camera_create(u32 width, u32 height) {
	Camera* camera = (Camera*) malloc(sizeof(Camera));
	if (!camera) {
		fprintf(stderr, "[ERROR] [Camera] Failed to allocate memory for camera!\n");
		goto error;
	}

	camera->position = (vec3) { 0.0f, 0.0f, 0.0f };
	camera->focal_length = 1.0f;

	camera->viewport = viewport_create(width, height);

	camera->sample_count = 10;

	return camera;

error:
	if (camera) { free(camera); }
	return NULL;
}

void camera_render(Camera* camera, Framebuffer* framebuffer, World* world) {
	for (usize s = 0; s < camera->sample_count; s++) {
		for (usize y = 0; y < framebuffer->height; y++) {
			for (usize x = 0; x < framebuffer->width; x++) {
				vec2 pixel_offset = (vec2) { ((x + (random_f32() - 0.5f)) * camera->viewport.delta.x), ((y + (random_f32() - 0.5f)) * camera->viewport.delta.y) };
				vec2 pixel_location = vec2_add(camera->viewport.first_pixel, pixel_offset);

				vec3 direction = vec3_sub((vec3) { pixel_location.x, pixel_location.y, -camera->focal_length }, camera->position);
				Ray ray = (Ray) { camera->position, direction };

				usize i = (y * framebuffer->width + x);
				framebuffer->pixels[i] = color_add(framebuffer->pixels[i], world_cast_ray(world, &ray, 0));
			}
		}
	}

	f32 sample_count_scale = 1.0f / camera->sample_count;
	for (usize i = 0; i < framebuffer->pixels_length; i++) {
		framebuffer->pixels[i] = color_scale(framebuffer->pixels[i], sample_count_scale);
	}
}

void camera_destroy(Camera* camera) {
	if (!camera) { return; }

	free(camera);
}
