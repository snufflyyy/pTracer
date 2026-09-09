#pragma once

#include "materials/material.h"
#include "color/color.h"

typedef struct MaterialMetal {
	Material material;

    Color color;
    f32 roughness;
} MaterialMetal;

MaterialMetal* material_metal_create(Color color, f32 roughness);
Color material_metal_get_color(MaterialMetal* metal);
vec3 material_metal_get_direction(MaterialMetal* metal, struct RayHit rayhit, u64* state);
void material_metal_destroy(MaterialMetal* metal);
