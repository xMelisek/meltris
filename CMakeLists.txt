cmake_minimum_required(VERSION 4.0)

project(meltris)
find_package(OpenGL REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_subdirectory(lib/glfw)
add_subdirectory(lib/glm)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories("glfw/deps")
include_directories("include/")
set(GLAD_GL "include/glad.h")

file(GLOB SOURCES "src/*.cpp" "src/**/*.cpp")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(meltris ${SOURCES})
target_link_libraries(meltris ${OPENGL_LIBRARIES} glfw glm::glm)

file(COPY ${CMAKE_SOURCE_DIR}/src/shaders/ DESTINATION ${CMAKE_BINARY_DIR}/bin/shaders/)
