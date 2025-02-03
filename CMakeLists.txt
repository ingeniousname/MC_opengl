cmake_minimum_required(VERSION 3.11)

project(MC)

file(GLOB SRC ./*.cpp)
file(GLOB APP_SRC "App/*.cpp")
file(GLOB CLOCK_SRC "Clock/*.cpp")
file(GLOB RENDERER_SRC "Renderer/*.cpp")
file(GLOB SHADER_SRC "Shader/*.cpp")
file(GLOB TEXTURE_SRC "Texture/*.cpp")

add_executable(MC ${SRC} ${APP_SRC} ${CLOCK_SRC} ${RENDERER_SRC} ${SHADER_SRC} ${TEXTURE_SRC})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/glfw)
include_directories(vendor/glfw/include)

add_subdirectory(vendor/glew/build/cmake)
include_directories(vendor/glew/include)

include_directories(MC .)
target_link_libraries(MC PRIVATE glfw glew opengl32)
