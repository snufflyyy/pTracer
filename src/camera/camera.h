#pragma once

#include <pthread.h>

#include "base-types.h"
#include "math/vec3/vec3.h"
#include "viewport/viewport.h"
#include "world/world.h"
#include "framebuffer/framebuffer.h"

#define CAMERA_DEFAULT_SAMPLE_COUNT 100

#define CAMERA_STARTING_TILE_SIZE 256
#define CAMERA_TARGET_TILES_PER_WORKER 16

typedef struct Camera {
	vec3 position;
	f32 focal_length;
	Viewport viewport;

	u32 sample_count;
} Camera;

typedef struct CameraRenderWork {
    FramebufferSection framebuffer_section;
} CameraRenderWork;

typedef struct CameraRenderWorker {
    pthread_t thread;

    u32 work_i;
} CameraRenderWorker;

Camera* camera_create(u32 framebuffer_width, u32 framebuffer_height);
void camera_render(Camera* camera, Framebuffer* framebuffer, World* world, u32 thread_count);
void camera_destroy(Camera* camera);
