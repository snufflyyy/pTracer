#pragma once

#include "rayhit/rayhit.h"
#include "math/ray/ray.h"

typedef struct Hittable {
	RayHit (*ray_hit)(struct Hittable* sphere, Ray* ray);
} Hittable;
