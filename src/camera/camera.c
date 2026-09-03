#include "camera.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base-types.h"
#include "color/color.h"
#include "math/vec3/vec3.h"
#include "math/ray/ray.h"
#include "world/world.h"

Camera* camera_create(u32 framebuffer_width, u32 framebuffer_height) {
	Camera* camera = (Camera*) malloc(sizeof(Camera));
	if (!camera) {
		fprintf(stderr, "[ERROR] [Camera] Failed to allocate memory for camera!\n");
		goto error;
	}

	camera->framebuffer_length = framebuffer_width * framebuffer_height;
	camera->framebuffer = (Color*) malloc(sizeof(Color) * camera->framebuffer_length);
	if (!camera->framebuffer) {
		fprintf(stderr, "[ERROR] [Camera] Failed to allocate memory for framebuffer!\n");
		goto error;
	}

	memset(camera->framebuffer, 0, sizeof(Color) * camera->framebuffer_length);

	camera->framebuffer_width = framebuffer_width;
	camera->framebuffer_height = framebuffer_height;

	camera->position = (vec3) { 0.0f, 0.0f, 0.0f };
	camera->focal_length = 1.0f;

	camera->viewport = viewport_create(framebuffer_width, framebuffer_height);

	return camera;

error:
	if (camera) {
		if (camera->framebuffer) { free(camera->framebuffer); }
		free(camera);
	}
	return NULL;
}

void camera_render(Camera* camera, World* world) {
	for (usize y = 0; y < camera->framebuffer_height; y++) {
		for (usize x = 0; x < camera->framebuffer_width; x++) {
			vec3 pixel_center = (vec3) { camera->viewport.first_pixel.x + (x * camera->viewport.pixel_delta.x), camera->viewport.first_pixel.y + (y * camera->viewport.pixel_delta.y), -camera->focal_length };
			vec3 direction = vec3_sub(pixel_center, camera->position);
			Ray ray = (Ray) { camera->position, direction };

			camera->framebuffer[y * camera->framebuffer_width + x] = world_cast_ray(world, &ray);
		}
	}
}

void camera_destroy(Camera* camera) {
	if (!camera) { return; }

	if (camera->framebuffer) { free(camera->framebuffer); }
	free(camera);
}
