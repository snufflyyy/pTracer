#include "vec3.h"

#include <math.h>

inline f32 vec3_length(vec3 a) {
	return sqrtf(vec3_length_squared(a));
}

inline f32 vec3_length_squared(vec3 a) {
	return (a.x * a.x) + (a.y * a.y) + (a.z * a.z);
}

inline vec3 vec3_normalized(vec3 a) {
	return vec3_scale(a, (1.0f / vec3_length(a)));
}

inline f32 vec3_dot(vec3 a, vec3 b) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

inline vec3 vec3_add(vec3 a, vec3 b) {
	return (vec3) { a.x + b.x, a.y + b.y, a.z + b.z };
}

inline vec3 vec3_sub(vec3 a, vec3 b) {
	return (vec3) { a.x - b.x, a.y - b.y, a.z - b.z };
}

inline vec3 vec3_scale(vec3 a, f32 scalar) {
	return (vec3) { a.x * scalar, a.y * scalar, a.z * scalar };
}
