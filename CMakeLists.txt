cmake_minimum_required(VERSION 3.16)
project(pTracer)

# needed for zed code editor
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
  src

  external/stb_image_write
)

add_executable(
  ${PROJECT_NAME}
  src/main.c

  src/math/random/random.c
  src/math/vec3/vec3.c
  src/math/vec2/vec2.c
  src/math/ray/ray.c
  src/math/angle/angle.c
  src/math/sphere/sphere.c

  src/color/color.c

  src/materials/diffuse/diffuse.c
  src/materials/metal/metal.c

  src/framebuffer/framebuffer.c

  src/viewport/viewport.c
  src/camera/camera.c

  src/world/world.c
  src/world/objects/objects.c
  src/world/objects/sphere/sphere.c

  src/image/image.c
)

target_link_libraries(${PROJECT_NAME} PRIVATE m)
