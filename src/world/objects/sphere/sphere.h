#pragma once

#include "materials/material.h"
#include "math/sphere/sphere.h"
#include "world/objects/objects.h"

typedef struct WorldObjectSphere {
	WorldObject object;
	Sphere sphere;
} WorldObjectSphere;

WorldObjectSphere* world_object_sphere_create(Sphere sphere, Material* material);
void world_object_sphere_destory(WorldObjectSphere* sphere_object);
