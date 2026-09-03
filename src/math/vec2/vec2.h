#pragma once

#include "base-types.h"

typedef struct vec2 {
	f32 x, y;
} vec2;

vec2 vec2_add(vec2 a, vec2 b);
