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

  src/math/vec3/vec3.c
  src/math/ray/ray.c

  src/color/color.c

  src/world/world.c
  src/sphere/sphere.c
  src/camera/camera.c
  src/viewport/viewport.c

  src/image/image.c
)
