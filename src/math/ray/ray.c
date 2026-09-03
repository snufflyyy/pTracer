#include "ray.h"

#include "math/vec3/vec3.h"

vec3 ray_at(Ray* ray, f32 t) {
	return vec3_add(ray->origin, vec3_scale(ray->direction, t));
}
