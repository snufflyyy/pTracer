#pragma once

#include "base-types.h"

typedef struct vec3 {
	f32 x, y, z;
} vec3;

f32 vec3_length(vec3 a);
f32 vec3_length_squared(vec3 a);
vec3 vec3_normalized(vec3 a);

f32 vec3_dot(vec3 a, vec3 b);

vec3 vec3_add(vec3 a, vec3 b);
vec3 vec3_sub(vec3 a, vec3 b);
vec3 vec3_scale(vec3 a, f32 scalar);
