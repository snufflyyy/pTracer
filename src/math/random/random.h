#pragma once

#include "base-types.h"
#include "math/vec3/vec3.h"

f32 random_f32(u64* state);
f32 random_f32_range(u64* state, f32 min, f32 max);

vec3 random_vec3(u64* state);
vec3 random_vec3_range(u64* state, f32 min, f32 max);
vec3 random_vec3_normalized(u64* state);
vec3 random_vec3_on_hemisphere(u64* state, vec3 normal);
