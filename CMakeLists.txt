cmake_minimum_required(VERSION 4.0)

project(meltris)
find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories("lib/glfw/deps")
set(GLAD_GL "lib/glfw/deps/glad/gl.h")

add_subdirectory(lib/glfw)

include_directories("./include/")

add_executable(meltris "src/main.cpp" ${GLAD_GL})
target_link_libraries(meltris ${OPENGL_LIBRARIES} glfw)
