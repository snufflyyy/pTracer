#include "objects.h"
#include "world/objects/sphere/sphere.h"

void world_object_destroy(WorldObject* object) {
	switch (object->type) {
		case WORLD_OBJECT_TYPE_SPHERE: world_object_sphere_destory((WorldObjectSphere*) object);
		default: break;
	}
}
