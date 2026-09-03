#pragma once

#include "hittables/hittable/hittable.h"
#include "math/vec3/vec3.h"
#include "base-types.h"
#include "math/ray/ray.h"
#include "rayhit/rayhit.h"

typedef struct Sphere {
	Hittable hittable;

	vec3 position;
	f32 radius;
} Sphere;

Sphere sphere_create(vec3 position, f32 radius);
RayHit sphere_ray_hit(Sphere* sphere, Ray* ray);
