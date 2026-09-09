#pragma once

#include "world/objects/objects.h"
#include "base-types.h"
#include "color/color.h"
#include "math/ray/ray.h"
#include "math/sphere/sphere.h"

#define WORLD_MAX_OBJECTS_COUNT 100
#define WORLD_MAX_RAY_BOUNCES 10
#define WORLD_DEFAULT_SKY_COLOR (Color) { 0.3f, 0.5f, 1.0f }

typedef struct World {
	WorldObject* objects[WORLD_MAX_OBJECTS_COUNT];
	u32 objects_count;

	u32 max_ray_bounces;

	Color sky_color;
} World;

World world_create();

void world_add_sphere(World* world, Sphere sphere, Material* material);

Color world_cast_ray(World* world, Ray* ray, u64* state, u32 bounces);
void world_destroy(World* world);
