#include "random.h"

#include <math.h>

#include "math/vec3/vec3.h"
#include "base-types.h"

u32 pcg32(u64* state) {
    u64 oldstate = *state;
    *state = oldstate * 6364136223846793005ULL + 1u;
    u32 xorshifted = (u32)(((oldstate >> 18u) ^ oldstate) >> 27u);
    u32 rot = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

inline f32 random_f32(u64* state) {
  return (pcg32(state) >> 8) * (1.0f / 16777216.0f);
}

inline f32 random_f32_range(u64* state, f32 min, f32 max) {
	return min + (max - min) * random_f32(state);
}

inline vec3 random_vec3(u64* state) {
	return (vec3) { random_f32(state), random_f32(state), random_f32(state) };
}

inline vec3 random_vec3_range(u64* state, f32 min, f32 max) {
	return (vec3) { random_f32_range(state, min, max), random_f32_range(state, min, max), random_f32_range(state, min, max) };
}

inline vec3 random_vec3_normalized(u64* state) {
	while (true) {
		vec3 point = random_vec3_range(state, -1.0f, 1.0f);
		f32 length_squared = vec3_length_squared(point);
		if (0.001f < length_squared && length_squared <= 1.0f) {
			return vec3_scale(point, 1.0f / sqrtf(length_squared));
		}
	}
}

inline vec3 random_vec3_on_hemisphere(u64* state, vec3 normal) {
	vec3 unit_sphere = random_vec3_normalized(state);
	if (vec3_dot(unit_sphere, normal) < 0.0f) {
		unit_sphere = vec3_scale(unit_sphere, -1.0f);
	}

	return unit_sphere;
}
