#pragma once

#include "math/vec3/vec3.h"
#include "base-types.h"
#include "math/ray/ray.h"
#include "rayhit/rayhit.h"

typedef struct Sphere {
	vec3 position;
	f32 radius;
} Sphere;

RayHit sphere_ray_hit(Sphere* sphere, Ray* ray, f32 t_min, f32 t_max);
