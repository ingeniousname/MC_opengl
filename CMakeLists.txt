cmake_minimum_required(VERSION 3.11)

project(MC)

file(GLOB SRC ./*.cpp)
file(GLOB APP_SRC "App/*.cpp")
file(GLOB CLOCK_SRC "Clock/*.cpp")
file(GLOB RENDERER_SRC "Renderer/*.cpp")
file(GLOB SHADER_SRC "Shader/*.cpp")
file(GLOB TEXTURE_SRC "Texture/*.cpp")


add_executable(MC ${SRC} ${APP_SRC} ${CLOCK_SRC}  ${RENDERER_SRC}  ${SHADER_SRC} ${TEXTURE_SRC})


include_directories(MC . )
target_link_libraries(MC PRIVATE -lglfw3 -lglew32 -lopengl32)
