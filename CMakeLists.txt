cmake_minimum_required(VERSION 4.0)

project(meltris)
find_package(OpenGL REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(lib/glfw)
add_subdirectory(lib/glm)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories("include/")

file(GLOB SOURCES "src/*.cpp" "src/**/*.cpp")

add_executable(meltris ${SOURCES})
target_link_libraries(meltris ${OPENGL_LIBRARIES} glfw glm::glm)

file(COPY ${CMAKE_SOURCE_DIR}/src/shaders/ DESTINATION ${CMAKE_BINARY_DIR}/bin/shaders/)
file(COPY ${CMAKE_SOURCE_DIR}/assets/ DESTINATION ${CMAKE_BINARY_DIR}/bin/assets/)
