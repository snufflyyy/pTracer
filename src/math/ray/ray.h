#pragma once

#include "math/vec3/vec3.h"

typedef struct Ray {
	vec3 origin;
	vec3 direction;
} Ray;

vec3 ray_at(Ray* ray, f32 t);
