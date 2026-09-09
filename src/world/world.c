#include "world.h"
#include "color/color.h"
#include "materials/material.h"
#include "rayhit/rayhit.h"
#include "world/objects/objects.h"
#include "world/objects/sphere/sphere.h"
#include <float.h>
#include <stdio.h>

World world_create() {
	World world = {0};

	world.max_ray_bounces = WORLD_MAX_RAY_BOUNCES;
	world.sky_color = WORLD_DEFAULT_SKY_COLOR;

	return world;
}

void world_add_sphere(World* world, Sphere sphere, Material* material) {
	if (world->objects_count >= WORLD_MAX_OBJECTS_COUNT) {
		fprintf(stderr, "[WORLD] Max object count reached! (%u)\n", WORLD_MAX_OBJECTS_COUNT);
		return;
	}

	world->objects[world->objects_count] = (WorldObject*) world_object_sphere_create(sphere, material);
	if (!world->objects[world->objects_count]) {
		fprintf(stderr, "[ERROR] [World] Failed to create sphere world object when adding sphere!\n");
		return;
	}
	world->objects_count++;
}

Color world_cast_ray(World* world, Ray* ray, u64* state, u32 bounces) {
	if (bounces >= world->max_ray_bounces) { return (Color) { 0.0f, 0.0f, 0.0f }; }

	RayHit rayhit = {0};
	f32 closest_t = FLT_MAX;
	Material* material = NULL;

	for (usize i = 0; i < world->objects_count; i++) {
		RayHit current_rayhit = world->objects[i]->ray_hit(world->objects[i], ray, 0.001f, closest_t);
		if (current_rayhit.hit) {
			rayhit = current_rayhit;
			closest_t = current_rayhit.t;
			material = world->objects[i]->material;
		}
	}

	if (rayhit.hit) {
		Color color = material->get_color(material);
		vec3 new_direction = material->get_direction(material, rayhit, state);

		Ray ray = (Ray) { rayhit.hit_position, new_direction };
		return color_mul(color, world_cast_ray(world, &ray, state, bounces + 1));
	}

	// sky
	vec3 direction_normalized = vec3_normalized(ray->direction);
	f32 a = 0.5f * (direction_normalized.y + 1.0f);
	return color_add(color_scale((Color) { 1.0f, 1.0f, 1.0f }, (1.0f - a)), color_scale(world->sky_color, a));
}

void world_destroy(World* world) {
	for (usize i = 0; i < world->objects_count; i++) {
		if (world->objects[i]) {
			if (world->objects[i]->material) { world->objects[i]->material->destroy(world->objects[i]->material); }
			world->objects[i]->destroy(world->objects[i]);
		}
	}
}
