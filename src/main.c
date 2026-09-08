#include <stdio.h>

#include "camera/camera.h"
#include "framebuffer/framebuffer.h"
#include "world/world.h"
#include "math/sphere/sphere.h"
#include "image/image.h"

#define IMAGE_WIDTH 640
#define IMAGE_HEIGHT 480

int main() {
	Framebuffer framebuffer = framebuffer_create(640, 480);

	Camera* camera = camera_create(IMAGE_WIDTH, IMAGE_HEIGHT);
	if (!camera) {
		fprintf(stderr, "[ERROR] Failed to create camera!\n");
		return 0;
	}

	World world = world_create();
	world_add_sphere(&world, (Sphere) { (vec3) { 0.0f, 0.0f, -4.0f }, 1.0f });
	world_add_sphere(&world, (Sphere) { (vec3) { 0.0f, -101.0f, -4.0f }, 100.0f });

	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);

	camera_render(camera, &framebuffer, &world, 16);

	clock_gettime(CLOCK_MONOTONIC, &end);

	f64 elapsed = (f64) (end.tv_sec - start.tv_sec) + (f64) (end.tv_nsec - start.tv_nsec) / 1e9;

	printf("Render time: %.2f seconds\n", elapsed);

	if (!image_create_png("../output.png", &framebuffer)) {
		fprintf(stderr, "[ERROR] Failed to export image!\n");
		return 0;
	}

	world_destroy(&world);
	camera_destroy(camera);
	framebuffer_destroy(&framebuffer);

	return 0;
}
