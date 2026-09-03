#include <stdio.h>

#include "camera/camera.h"
#include "world/world.h"
#include "sphere/sphere.h"
#include "image/image.h"

#define IMAGE_WIDTH 640
#define IMAGE_HEIGHT 480

int main() {
	Camera* camera = camera_create(IMAGE_WIDTH, IMAGE_HEIGHT);
	if (!camera) {
		fprintf(stderr, "[ERROR] Failed to create camera!\n");
		return 0;
	}

	World world = world_create();

	Sphere sphere = sphere_create((vec3) { 0.0f, 0.0f, -1.0f }, 0.5f);
	world_add_hittable(&world, sphere.hittable);

	camera_render(camera, &world);

	if (!image_create_png("../output.png", camera->framebuffer, camera->framebuffer_width, camera->framebuffer_height)) {
		fprintf(stderr, "[ERROR] Failed to export image!\n");
		return 0;
	}

	camera_destroy(camera);

	return 0;
}
