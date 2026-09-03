#pragma once

#include "base-types.h"
#include "math/vec3/vec3.h"

typedef struct RayHit {
	bool hit;
	f32 t;
	vec3 normal;
	vec3 hit_position;
} RayHit;
