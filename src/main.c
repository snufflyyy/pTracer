#include <stdio.h>
#include <time.h>

#include "camera/camera.h"
#include "framebuffer/framebuffer.h"
#include "math/random/random.h"
#include "world/world.h"
#include "math/sphere/sphere.h"
#include "image/image.h"

#define IMAGE_WIDTH 640
#define IMAGE_HEIGHT 480

int main() {
	random_set_seed(time(NULL));

	Framebuffer framebuffer = framebuffer_create(640, 480);

	Camera* camera = camera_create(IMAGE_WIDTH, IMAGE_HEIGHT);
	if (!camera) {
		fprintf(stderr, "[ERROR] Failed to create camera!\n");
		return 0;
	}

	World world = world_create();
	world_add_sphere(&world, (Sphere) { (vec3) { 0.0f, 0.0f, -4.0f }, 1.0f });
	world_add_sphere(&world, (Sphere) { (vec3) { 0.0f, -101.0f, -4.0f }, 100.0f });

	camera_render(camera, &framebuffer, &world);

	if (!image_create_png("../output.png", &framebuffer)) {
		fprintf(stderr, "[ERROR] Failed to export image!\n");
		return 0;
	}

	world_destroy(&world);
	camera_destroy(camera);
	framebuffer_destroy(&framebuffer);

	return 0;
}
