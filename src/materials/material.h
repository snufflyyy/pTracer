#pragma once

#include "color/color.h"
#include "math/vec3/vec3.h"

typedef enum MaterialType {
	MATERIAL_TYPE_NONE,
	MATERIAL_TYPE_DIFFUSE,
	MATERIAL_TYPE_METAL,
} MaterialType;

struct RayHit;

typedef struct Material {
	MaterialType type;

	Color (*get_color)(struct Material* material);
	vec3 (*get_direction)(struct Material* material, struct RayHit rayhit, u64* state);
	void (*destroy)(struct Material* material);
} Material;
