#pragma once

#include "math/sphere/sphere.h"
#include "world/objects/objects.h"

typedef struct WorldObjectSphere {
	WorldObject object;
	Sphere sphere;
} WorldObjectSphere;

WorldObjectSphere* world_object_sphere_create(Sphere sphere);
void world_object_sphere_destory(WorldObjectSphere* sphere_object);
