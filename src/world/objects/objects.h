#pragma once

#include "rayhit/rayhit.h"
#include "math/ray/ray.h"

typedef enum WorldObjectType {
	WORLD_OBJECT_TYPE_NONE,
	WORLD_OBJECT_TYPE_SPHERE,
} WorldObjectType;

typedef struct WorldObject {
	WorldObjectType type;

	RayHit (*ray_hit)(struct WorldObject* object, Ray* ray, f32 t_min, f32 t_max);
	void (*destroy)(struct WorldObject* object);
} WorldObject;
