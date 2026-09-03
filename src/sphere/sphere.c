#include "sphere.h"

#include <math.h>

#include "hittables/hittable/hittable.h"
#include "math/ray/ray.h"
#include "math/vec3/vec3.h"

RayHit sphere_hittable_ray_hit(Hittable* hittable, Ray* ray) {
	return sphere_ray_hit((Sphere*) hittable, ray);
}

Sphere sphere_create(vec3 position, f32 radius) {
	return (Sphere) { sphere_hittable_ray_hit, position, radius };
}

RayHit sphere_ray_hit(Sphere* sphere, Ray* ray) {
	RayHit rayhit = {0};

	vec3 oc = vec3_sub(sphere->position, ray->origin);
	f32 a = vec3_dot(ray->direction, ray->direction);
	f32 b = -2.0f - vec3_dot(ray->direction, oc);
	f32 c = vec3_dot(oc, oc) - (sphere->radius * sphere->radius);
	f32 discriminant = (b * b) - 4 * a * c;

	if (discriminant < 0) { return rayhit; } // no hit

	rayhit.hit = true;
	rayhit.t = (-b - sqrtf(discriminant) ) / (2.0f * a);
	rayhit.hit_position = ray_at(ray, rayhit.t);
	rayhit.normal = vec3_sub(rayhit.hit_position, sphere->position);

	return rayhit;
}
