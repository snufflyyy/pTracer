#pragma once

#include "color/color.h"

typedef struct Framebuffer {
	Color* pixels;
	usize pixels_length;

	u32 width, height;
} Framebuffer;

typedef struct FramebufferSection {
    u32 start_x, end_x;
    u32 start_y, end_y;
} FramebufferSection;

Framebuffer framebuffer_create(u32 width, u32 height);
void framebuffer_destroy(Framebuffer* framebuffer);
