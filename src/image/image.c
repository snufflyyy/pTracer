#include "image.h"
#include <stdio.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

typedef struct ColorRGB {
	u8 red, green, blue;
} ColorRGB;

bool image_create_png(const char* filename, Color* framebuffer, u32 width, u32 height) {
	usize color_rgb_framebuffer_length = width * height;
	ColorRGB* color_rgb_framebuffer = (ColorRGB*) malloc(sizeof(ColorRGB) * color_rgb_framebuffer_length);
	if (!color_rgb_framebuffer) {
		fprintf(stderr, "[ERROR] [Image] Failed to allocate memory for rgb framebuffer!\n");
		goto error;
	}

	// convert Color, which uses floats, to ColorRGB, which uses u8 (0-255)
	for (usize i = 0; i < color_rgb_framebuffer_length; i++) {
		color_rgb_framebuffer[i] = (ColorRGB) { (u8) 255 * framebuffer[i].red, (u8) 255 * framebuffer[i].green, (u8) 255 * framebuffer[i].blue };
	}

	if (stbi_write_png(filename, width, height, 3, color_rgb_framebuffer, width * 3) == 0) {
		fprintf(stderr, "[ERROR] [Image] Failed to write png!\n");
		goto error;
	}

	free(color_rgb_framebuffer);
	return true;

error:
	if (color_rgb_framebuffer) { free(color_rgb_framebuffer); }
	return false;
}
