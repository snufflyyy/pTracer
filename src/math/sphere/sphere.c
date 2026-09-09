#include "sphere.h"

#include <math.h>

#include "math/ray/ray.h"
#include "math/vec3/vec3.h"

RayHit sphere_ray_hit(Sphere* sphere, Ray* ray, f32 t_min, f32 t_max) {
	RayHit rayhit = {0};

	vec3 oc = vec3_sub(sphere->position, ray->origin);
	f32 a = vec3_length_squared(ray->direction);
	f32 h = vec3_dot(ray->direction, oc);
	f32 c = vec3_length_squared(oc) - (sphere->radius * sphere->radius);

	f32 discriminant = (h * h) - (a * c);
	if (discriminant < 0.0f) { return rayhit; } // no hit

	f32 discriminant_sqrt = sqrtf(discriminant);

	f32 root = (h - discriminant_sqrt) / a;
	if (root <= t_min || root >= t_max) {
		root = (h + discriminant_sqrt) / a;
		if (root <= t_min || root >= t_max) { return rayhit; }
	}

	rayhit.hit = true;
	rayhit.ray = *ray;
	rayhit.t = root;
	rayhit.hit_position = ray_at(ray, rayhit.t);
	rayhit.normal = vec3_scale(vec3_sub(rayhit.hit_position, sphere->position), 1.0f / sphere->radius);
	rayhit.front_face = true;

	if (vec3_dot(ray->direction, rayhit.normal) > 0.0f) {
		rayhit.normal = vec3_scale(rayhit.normal, -1.0f);
		rayhit.front_face = false;
	}

	return rayhit;
}
