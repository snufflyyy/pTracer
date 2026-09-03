#pragma once

#include "base-types.h"
#include "math/vec3/vec3.h"

void random_set_seed(u32 seed);

f32 random_f32();
f32 random_f32_range(f32 min, f32 max);

vec3 random_vec3();
vec3 random_vec3_range(f32 min, f32 max);
vec3 random_vec3_normalized();
vec3 random_vec3_on_hemisphere(vec3 normal);
