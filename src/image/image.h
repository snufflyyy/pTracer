#pragma once

#include "base-types.h"
#include "color/color.h"

bool image_create_png(const char* filename, Color* framebuffer, u32 width, u32 height);
