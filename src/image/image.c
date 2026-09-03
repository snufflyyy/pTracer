#include "image.h"

#include <math.h>
#include <stdio.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

typedef struct ColorRGB {
	u8 red, green, blue;
} ColorRGB;

f32 linear_to_gamma(f32 linear) {
	if (linear <= 0) { return 0.0f; }

	return sqrtf(linear);
}

bool image_create_png(const char* filename, Framebuffer* framebuffer) {
	ColorRGB* color_rgb_framebuffer = (ColorRGB*) malloc(sizeof(ColorRGB) * framebuffer->pixels_length);
	if (!color_rgb_framebuffer) {
		fprintf(stderr, "[ERROR] [Image] Failed to allocate memory for rgb framebuffer!\n");
		goto error;
	}

	// convert Color, which uses floats, to ColorRGB, which uses u8 (0-255)
	for (usize i = 0; i < framebuffer->pixels_length; i++) {
		color_rgb_framebuffer[i] = (ColorRGB) { (u8) 255 * linear_to_gamma(framebuffer->pixels[i].red), (u8) 255 * linear_to_gamma(framebuffer->pixels[i].green), (u8) 255 * linear_to_gamma(framebuffer->pixels[i].blue) };
	}

	if (stbi_write_png(filename, framebuffer->width, framebuffer->height, 3, color_rgb_framebuffer, framebuffer->width * 3) == 0) {
		fprintf(stderr, "[ERROR] [Image] Failed to write png!\n");
		goto error;
	}

	free(color_rgb_framebuffer);
	return true;

error:
	if (color_rgb_framebuffer) { free(color_rgb_framebuffer); }
	return false;
}
