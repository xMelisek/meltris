cmake_minimum_required(VERSION 4.0)

project(meltris)
find_package(OpenGL REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_subdirectory(lib/glfw)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories("glfw/deps")
set(GLAD_GL "lib/glfw/deps/glad/gl.h")

file(GLOB SOURCES "src/*.cpp" "src/**/*.cpp")

add_executable(meltris ${SOURCES} ${GLAD_GL})
target_link_libraries(meltris ${OPENGL_LIBRARIES} glfw)

file(COPY ${CMAKE_SOURCE_DIR}/src/shaders/ DESTINATION ${CMAKE_BINARY_DIR}/bin/shaders/)
