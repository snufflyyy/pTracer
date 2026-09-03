#include "random.h"

#include <stdlib.h>
#include <math.h>

#include "math/vec3/vec3.h"
#include "base-types.h"

void random_set_seed(u32 seed) {
	srand(seed);
}

inline f32 random_f32() {
	return rand() / (RAND_MAX + 1.0f);
}

inline f32 random_f32_range(f32 min, f32 max) {
	return min + (max - min) * random_f32();
}

inline vec3 random_vec3() {
	return (vec3) { random_f32(), random_f32(), random_f32() };
}

inline vec3 random_vec3_range(f32 min, f32 max) {
	return (vec3) { random_f32_range(min, max), random_f32_range(min, max), random_f32_range(min, max) };
}

inline vec3 random_vec3_normalized() {
	while (true) {
		vec3 point = random_vec3_range(-1.0f, 1.0f);
		f32 length_squared = vec3_length_squared(point);
		if (0.001f < length_squared && length_squared <= 1.0f) {
			return vec3_scale(point, 1.0f / sqrtf(length_squared));
		}
	}
}

inline vec3 random_vec3_on_hemisphere(vec3 normal) {
	vec3 unit_sphere = random_vec3_normalized();
	if (vec3_dot(unit_sphere, normal) < 0.0f) {
		unit_sphere = vec3_scale(unit_sphere, -1.0f);
	}

	return unit_sphere;
}
