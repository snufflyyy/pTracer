#pragma once

#include "base-types.h"

typedef struct Color {
	f32 red, green, blue;
} Color;

Color color_scale(Color color, f32 scalar);
Color color_mul(Color a, Color b);
Color color_add(Color a, Color b);
