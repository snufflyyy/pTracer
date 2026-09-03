#pragma once

#include "base-types.h"
#include "color/color.h"
#include "framebuffer/framebuffer.h"

bool image_create_png(const char* filename, Framebuffer* framebuffer);
