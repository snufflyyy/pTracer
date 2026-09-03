#pragma once

#include "color/color.h"

typedef struct Framebuffer {
	Color* pixels;
	usize pixels_length;

	u32 width, height;
} Framebuffer;

Framebuffer framebuffer_create(u32 width, u32 height);
void framebuffer_destroy(Framebuffer* framebuffer);
