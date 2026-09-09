#include "camera.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "base-types.h"
#include "color/color.h"
#include "framebuffer/framebuffer.h"
#include "math/vec2/vec2.h"
#include "math/vec3/vec3.h"
#include "math/ray/ray.h"
#include "math/random/random.h"
#include "world/world.h"

Camera* camera_create(u32 framebuffer_width, u32 framebuffer_height, f32 fov) {
	Camera* camera = (Camera*) malloc(sizeof(Camera));
	if (!camera) {
		fprintf(stderr, "[ERROR] [Camera] Failed to allocate memory for camera!\n");
		goto error;
	}

	camera->position = (vec3) { 0.0f, 0.0f, 0.0f };

	camera->viewport = viewport_create(framebuffer_width, framebuffer_height, fov);

	return camera;

error:
	if (camera) { free(camera); }
	return NULL;
}

struct CameraRenderWorkerContext {
    CameraRenderWorker* worker;

    Camera* camera;
    u32 sample_count;
    World* world;

    Framebuffer* framebuffer;
    CameraRenderWork* work;
    u32 work_length;
    u32* next_work_i;
    u64 state;
    pthread_mutex_t* mutex;
};

void* camera_render_worker_work(void* context_ptr) {
    struct CameraRenderWorkerContext* context = (struct CameraRenderWorkerContext*) context_ptr;
    CameraRenderWorker* worker = context->worker;

    while (true) {
        pthread_mutex_lock(context->mutex);

        if (*context->next_work_i >= context->work_length) {
            pthread_mutex_unlock(context->mutex);
            break;
        }

        u32 job_i = *context->next_work_i;
        (*context->next_work_i)++;

        pthread_mutex_unlock(context->mutex);

        worker->work_i = job_i;

        f32 sample_scale = 1.0f / context->sample_count;

  		for (usize y = context->work[worker->work_i].framebuffer_section.start_y; y < context->work[worker->work_i].framebuffer_section.end_y; y++) {
 			for (usize x = context->work[worker->work_i].framebuffer_section.start_x; x < context->work[worker->work_i].framebuffer_section.end_x; x++) {
                Color accumulated_color = (Color) { 0.0f, 0.0f, 0.0f };

                for (usize s = 0; s < context->sample_count; s++) {
                    vec2 random_offset = (vec2) { (random_f32(&context->state) - 0.5f), (random_f32(&context->state) - 0.5f) };
                    vec2 pixel_offset = (vec2) { ((x + random_offset.x) * context->camera->viewport.delta.x), ((y + random_offset.y) * context->camera->viewport.delta.y) };
                    vec2 pixel_location = vec2_add(context->camera->viewport.first_pixel, pixel_offset);

                    vec3 pixel_position = vec3_add(context->camera->position, (vec3) { pixel_location.x, pixel_location.y, -1.0f });

                    vec3 direction = vec3_sub(pixel_position, context->camera->position);
                    Ray ray = (Ray) { context->camera->position, direction };

                    accumulated_color = color_add(accumulated_color, world_cast_ray(context->world, &ray, &context->state, 0));
                }

                context->framebuffer->pixels[y * context->framebuffer->width + x] = color_scale(accumulated_color, sample_scale);
 			}
  		}
   	}

    return NULL;
}

void camera_render(Camera* camera, Framebuffer* framebuffer, World* world, u32 sample_count, u32 thread_count) {
	struct timespec start, end;

	clock_gettime(CLOCK_MONOTONIC, &start);

    u32 tile_size = CAMERA_STARTING_TILE_SIZE;
    u32 target_tiles_per_worker = thread_count * CAMERA_TARGET_TILES_PER_WORKER;

    u32 x_scale = framebuffer->width / tile_size + (framebuffer->width % tile_size != 0);
    u32 y_scale = framebuffer->height / tile_size + (framebuffer->height % tile_size != 0);
    u32 work_length = x_scale * y_scale;

    while (work_length < target_tiles_per_worker && tile_size > 8) {
        tile_size /= 2;
        x_scale = framebuffer->width / tile_size + (framebuffer->width % tile_size != 0);
        y_scale = framebuffer->height / tile_size + (framebuffer->height % tile_size != 0);
        work_length = x_scale * y_scale;
    }

    CameraRenderWork* work = malloc(sizeof(CameraRenderWork) * work_length);
    if (!work) {
        fprintf(stderr, "[ERROR] Failed to allocate work buffer!\n");
        return;
    }

    for (usize y = 0; y < y_scale ; y++) {
        for (usize x = 0; x < x_scale; x++) {
            u32 start_x = x * tile_size;
            u32 start_y = y * tile_size;

            u32 width = framebuffer->width - start_x;
            u32 height = framebuffer->height - start_y;

            if (width > tile_size) { width = tile_size; }
            if (height > tile_size) { height = tile_size; }

            work[y * x_scale + x].framebuffer_section = (FramebufferSection) {
                .start_x = start_x,
                .end_x = start_x + width,
                .start_y = start_y,
                .end_y = start_y + height,
            };
        }
    }

    CameraRenderWorker* workers = (CameraRenderWorker*) malloc(sizeof(CameraRenderWorker) * thread_count);
    if (!workers) {
        fprintf(stderr, "[ERROR] Failed to allocate workers!\n");
        return;
    }
    struct CameraRenderWorkerContext* contexts = (struct CameraRenderWorkerContext*) malloc(sizeof(struct CameraRenderWorkerContext) * thread_count);
    if (!contexts) {
        fprintf(stderr, "[ERROR] Failed to allocate contexts!\n");
        return;
    }

    u32 next_work_i = 0;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    for (usize i = 0; i < thread_count; i++) {
        u64 state = time(NULL) * (88172645463325252ULL + i); // probably find a like correct way of doing this
        contexts[i] = (struct CameraRenderWorkerContext) { &workers[i], camera, sample_count, world, framebuffer, work, work_length, &next_work_i, state, &mutex };
        workers[i].work_i = i;
        pthread_create(&workers[i].thread, NULL, camera_render_worker_work, &contexts[i]); // error check this
    }

    for (usize i = 0; i < thread_count; i++) {
        pthread_join(workers[i].thread, NULL);
    }

	pthread_mutex_destroy(&mutex);
	free(contexts);
	free(workers);
	free(work);

	clock_gettime(CLOCK_MONOTONIC, &end);

	f64 elapsed = (f64) (end.tv_sec - start.tv_sec) + (f64) (end.tv_nsec - start.tv_nsec) / 1e9;
	printf("[INFO] [Camera] Render took %.2f seconds!\n", elapsed);
}

void camera_destroy(Camera* camera) {
	if (!camera) { return; }

	free(camera);
}
