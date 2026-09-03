#pragma once

#include "world/objects/objects.h"
#include "base-types.h"
#include "color/color.h"
#include "math/ray/ray.h"
#include "math/sphere/sphere.h"

#define WORLD_MAX_OBJECTS_COUNT 100

typedef struct World {
	WorldObject* objects[WORLD_MAX_OBJECTS_COUNT];
	u32 objects_count;

	u32 max_ray_bounces;
} World;

World world_create();

void world_add_sphere(World* world, Sphere sphere);

Color world_cast_ray(World* world, Ray* ray, u32 bounces);
void world_destroy(World* world);
