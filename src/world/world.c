#include "world.h"
#include "color/color.h"
#include "math/random/random.h"
#include "rayhit/rayhit.h"
#include "world/objects/objects.h"
#include "world/objects/sphere/sphere.h"
#include <float.h>
#include <stdio.h>

World world_create() {
	World world = {0};

	world.max_ray_bounces = 10;

	world.sky_color = WORLD_DEFAULT_SKY_COLOR;

	return world;
}

void world_add_sphere(World* world, Sphere sphere) {
	if (world->objects_count >= WORLD_MAX_OBJECTS_COUNT) {
		fprintf(stderr, "[WORLD] Max object count reached! (%u)\n", WORLD_MAX_OBJECTS_COUNT);
		return;
	}

	world->objects[world->objects_count] = (WorldObject*) world_object_sphere_create(sphere);
	if (!world->objects[world->objects_count]) {
		fprintf(stderr, "[ERROR] [World] Failed to create sphere world object when adding sphere!\n");
		return;
	}
	world->objects_count++;
}


Color world_cast_ray(World* world, Ray* ray, u64* state, u32 bounces) {
	if (bounces >= world->max_ray_bounces) { return (Color) { 0.0f, 0.0f, 0.0f }; }

	RayHit closest_hit = {0};
	f32 closest_t = FLT_MAX;

	for (usize i = 0; i < world->objects_count; i++) {
		RayHit rayhit = world->objects[i]->ray_hit(world->objects[i], ray, 0.001f, closest_t);
		if (rayhit.hit) {
			closest_hit = rayhit;
			closest_t = rayhit.t;
		}
	}

	if (closest_hit.hit) {
		Ray ray = (Ray) { closest_hit.hit_position, vec3_add(closest_hit.normal, random_vec3_normalized(state)) };
		return color_scale(world_cast_ray(world, &ray, state, bounces + 1), 0.5f);
	}

	// sky
	vec3 direction_normalized = vec3_normalized(ray->direction);
	f32 a = 0.5f * (direction_normalized.y + 1.0f);
	return color_add(color_scale((Color) { 1.0f, 1.0f, 1.0f }, (1.0f - a)), color_scale(world->sky_color, a));
}

void world_destroy(World* world) {
	for (usize i = 0; i < world->objects_count; i++) {
		if (world->objects[i]) { world->objects[i]->destroy(world->objects[i]); }
	}
}
