#include "framebuffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Framebuffer framebuffer_create(u32 width, u32 height) {
	Framebuffer framebuffer = {0};

	framebuffer.pixels_length = width * height;
	framebuffer.pixels = (Color*) malloc(sizeof(Color) * framebuffer.pixels_length);
	if (!framebuffer.pixels) {
		fprintf(stderr, "[ERROR] [Framebuffer] Failed to allocate memory for pixels!\n");
		return framebuffer;
	}

	framebuffer.width = width;
	framebuffer.height = height;

	memset(framebuffer.pixels, 0, sizeof(Color) * framebuffer.pixels_length);

	return framebuffer;
}

void framebuffer_destroy(Framebuffer* framebuffer) {
	if (framebuffer->pixels) { free(framebuffer->pixels); }
}
