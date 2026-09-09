#include <stdio.h>

#include "camera/camera.h"
#include "framebuffer/framebuffer.h"
#include "materials/diffuse/diffuse.h"
#include "materials/metal/metal.h"
#include "materials/material.h"
#include "world/world.h"
#include "math/sphere/sphere.h"
#include "image/image.h"

// 16:9 480p
#define IMAGE_WIDTH 854
#define IMAGE_HEIGHT 480

#define CAMERA_FOV 55.0f

#define SAMPLE_COUNT 100
#define THREAD_COUNT 8

int main() {
	Framebuffer framebuffer = framebuffer_create(IMAGE_WIDTH, IMAGE_HEIGHT);
	Camera* camera = camera_create(framebuffer.width, framebuffer.height, CAMERA_FOV);
	if (!camera) {
		fprintf(stderr, "[ERROR] Failed to create camera!\n");
		framebuffer_destroy(&framebuffer);
		return -1;
	}

	camera->position = (vec3) { 0.0f, 0.0f, 5.0f };

	World world = world_create();
	world_add_sphere(&world, (Sphere) { (vec3) { 0.0f, 0.0f, 0.0f }, 1.0f }, (Material*) material_metal_create((Color) { 0.3f, 0.5f, 0.8f }, 0.0f));
	world_add_sphere(&world, (Sphere) { (vec3) { 0.0f, -101.0f, 0.0f }, 100.0f }, (Material*) material_diffuse_create((Color) { 0.5f, 0.5f, 0.5f }));

	camera_render(camera, &framebuffer, &world, SAMPLE_COUNT, THREAD_COUNT);

	if (!image_create_png("../output.png", &framebuffer)) {
		fprintf(stderr, "[ERROR] Failed to export image!\n");
		world_destroy(&world);
		camera_destroy(camera);
		framebuffer_destroy(&framebuffer);
		return -1;
	}

	world_destroy(&world);
	camera_destroy(camera);
	framebuffer_destroy(&framebuffer);

	return 0;
}
