#pragma once

#include "hittables/hittable/hittable.h"
#include "base-types.h"
#include "color/color.h"
#include "math/ray/ray.h"

#define WORLD_MAX_HITTABLES_COUNT 100

typedef struct World {
	Hittable hittables[WORLD_MAX_HITTABLES_COUNT];
	u32 hittables_count;
} World;

World world_create();
void world_add_hittable(World* world, Hittable hittable);
Color world_cast_ray(World* world, Ray* ray);
void world_destroy(World* world);
