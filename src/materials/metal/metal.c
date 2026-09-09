#include "metal.h"

#include <stdlib.h>
#include <stdio.h>

#include "math/random/random.h"
#include "math/vec3/vec3.h"
#include "rayhit/rayhit.h"
#include "base-types.h"

static Color get_color(Material* material) {
	return material_metal_get_color((MaterialMetal*) material);
}

static vec3 get_direction(Material* material, RayHit rayhit, u64* state) {
	return material_metal_get_direction((MaterialMetal*) material, rayhit, state);
}

static void material_destory(Material* material) {
	material_metal_destroy((MaterialMetal*) material);
}

MaterialMetal* material_metal_create(Color color, f32 roughness) {
	MaterialMetal* metal = (MaterialMetal*) malloc(sizeof(MaterialMetal));
	if (!metal) {
		fprintf(stderr, "[ERROR] [Material] Failed to allocate memory for metal material!\n");
		return NULL;
	}

	metal->material = (Material) {
		.type = MATERIAL_TYPE_METAL,
		.get_color = get_color,
		.get_direction = get_direction,
		.destroy = material_destory,
	};

	metal->color = color;
	metal->roughness = roughness;

	return metal;
}

Color material_metal_get_color(MaterialMetal* metal) {
	return metal->color;
}

vec3 material_metal_get_direction(MaterialMetal* metal, struct RayHit rayhit, u64* state) {
	vec3 reflected = vec3_reflect(rayhit.ray.direction, rayhit.normal);
	return vec3_add(vec3_normalized(reflected), vec3_scale(random_vec3_normalized(state), metal->roughness));
}

void material_metal_destroy(MaterialMetal* metal) {
	if (metal) { free(metal); }
}
