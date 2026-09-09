#include "diffuse.h"

#include <stdio.h>
#include <stdlib.h>

#include "materials/material.h"
#include "math/random/random.h"
#include "rayhit/rayhit.h"
#include "math/random/random.h"

static Color get_color(Material* material) {
	return material_diffuse_get_color((MaterialDiffuse*) material);
}

static vec3 get_direction(Material* material, RayHit rayhit, u64* state) {
	return material_diffuse_get_direction((MaterialDiffuse*) material, rayhit, state);
}

static void material_destory(Material* material) {
	material_diffuse_destroy((MaterialDiffuse*) material);
}

MaterialDiffuse* material_diffuse_create(Color color) {
	MaterialDiffuse* diffuse = (MaterialDiffuse*) malloc(sizeof(MaterialDiffuse));
	if (!diffuse) {
		fprintf(stderr, "[ERROR] [Material] Failed to allocate memory for diffuse material\n");
		return NULL;
	}

	diffuse->material = (Material) {
		.type = MATERIAL_TYPE_DIFFUSE,
		.get_color = get_color,
		.get_direction = get_direction,
		.destroy = material_destory,
	};

	diffuse->color = color;

	return diffuse;
}

inline Color material_diffuse_get_color(MaterialDiffuse* diffuse) {
	return diffuse->color;
}

inline vec3 material_diffuse_get_direction(MaterialDiffuse* diffuse, RayHit rayhit, u64* state) {
	return vec3_normalized(vec3_add(rayhit.normal, random_vec3_normalized(state)));
}

void material_diffuse_destroy(MaterialDiffuse* diffuse) {
	if (diffuse) { free(diffuse); }
}
