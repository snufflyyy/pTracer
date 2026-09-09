#include "sphere.h"

#include "world/objects/objects.h"

#include <stdio.h>
#include <stdlib.h>

static RayHit ray_hit(WorldObject* object, Ray* ray, f32 t_min, f32 t_max) {
	return sphere_ray_hit(&((WorldObjectSphere*) object)->sphere, ray, t_min, t_max);
}

static void sphere_destroy(WorldObject* object) {
	world_object_sphere_destory((WorldObjectSphere*) object);
}

WorldObjectSphere* world_object_sphere_create(Sphere sphere, Material* material) {
	WorldObjectSphere* object = (WorldObjectSphere*) malloc(sizeof(WorldObjectSphere));
	if (!object) {
		fprintf(stderr, "[ERROR] [World] [Sphere] Failed to allocate memory for sphere world object!\n");
		return NULL;
	}

	object->object = (WorldObject) {
		.type = WORLD_OBJECT_TYPE_SPHERE,
		.material = material,
		.ray_hit = ray_hit,
		.destroy = sphere_destroy,
 	};
	object->sphere = sphere;

	return object;
}

void world_object_sphere_destory(WorldObjectSphere* sphere_object) {
	if (!sphere_object) { return; }

	free(sphere_object);
}
