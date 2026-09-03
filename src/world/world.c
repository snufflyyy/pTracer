#include "world.h"
#include "color/color.h"
#include "hittables/hittable/hittable.h"
#include "rayhit/rayhit.h"
#include <stdio.h>

World world_create() {
	return (World) {0};
}

void world_add_hittable(World* world, Hittable sphere) {
	if (world->hittables_count >= WORLD_MAX_HITTABLES_COUNT) {
		fprintf(stderr, "[WORLD] Max sphere count reached! (%u)\n", WORLD_MAX_HITTABLES_COUNT);
		return;
	}

	world->hittables[world->hittables_count] = sphere;
	world->hittables_count++;
}

Color world_cast_ray(World* world, Ray* ray) {
	for (usize i = 0; i < world->hittables_count; i++) {
		RayHit rayhit = world->hittables[i].ray_hit(&world->hittables[i], ray);
		if (rayhit.hit) {
			return color_scale((Color) { 1.0f + rayhit.normal.x, 1.0f + rayhit.normal.y, 1.0f + rayhit.normal.z }, 0.5f);
		}
	}

	// sky
	vec3 direction_normalized = vec3_normalized(ray->direction);
	f32 a = 0.5f * (direction_normalized.y + 1.0f);
	return color_add(color_scale((Color) { 1.0f, 1.0f, 1.0f }, (1.0f - a)), color_scale((Color) { 0.5f, 0.7f, 1.0f }, a));
}

void world_destroy(World* world) {
	// nothing for now
}
