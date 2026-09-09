#pragma once

#include "materials/material.h"
#include "color/color.h"

typedef struct MaterialDiffuse {
	Material material;

	Color color;
} MaterialDiffuse;

MaterialDiffuse* material_diffuse_create(Color color);
Color material_diffuse_get_color(MaterialDiffuse* diffuse);
vec3 material_diffuse_get_direction(MaterialDiffuse* diffuse, struct RayHit rayhit, u64* state);
void material_diffuse_destroy(MaterialDiffuse* diffuse);
