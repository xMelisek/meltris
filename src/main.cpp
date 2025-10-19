#define GLAD_GL_IMPLEMENTATION
#include "../include/glad.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#include "../lib/glfw/deps/linmath.h"
#include "util/shader.h"
#include "util/util.h"

struct Vertex {
  vec2 pos;
  vec3 col;
};

static const Vertex vertices[3] = {{{-0.6f, -0.4f}, {0.05f, 0.05f, 0.05f}},
                                   {{0.6f, -0.4f}, {0.05f, 0.05f, 0.05f}},
                                   {{0.f, 0.6f}, {0.05f, 0.05f, 0.05f}}};

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

static void cursor_position_callback(GLFWwindow *window, double xpos,
                                     double ypos) {
  std::cout << "Position: " << xpos << "," << ypos << std::endl;
}

static void error_callback(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

int main(void) {
  glfwSetErrorCallback(error_callback);
  GLFWwindow* window;
  if (!glfwInit()) {
     perror("GLFW not initialized!");
     exit(EXIT_FAILURE);
   }

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   window = glfwCreateWindow(1280, 720, "Meltris", NULL, NULL);
   if (!window) {
     glfwTerminate();
     exit(EXIT_FAILURE);
   }

   glfwSetKeyCallback(window, key_callback);
   glfwSetCursorPosCallback(window, cursor_position_callback);

   glfwMakeContextCurrent(window);
   gladLoadGL(glfwGetProcAddress);
   glfwSwapInterval(1);
  util::init();

  GLuint vertex_buffer;
  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  const GLuint program = createBaseProgram();

  const GLint mvp_location = glGetUniformLocation(program, "MVP");
  const GLint vpos_location = glGetAttribLocation(program, "vPos");
  const GLint vcol_location = glGetAttribLocation(program, "vCol");

  GLuint vertex_array;
  glGenVertexArrays(1, &vertex_array);
  glBindVertexArray(vertex_array);
  glEnableVertexAttribArray(vpos_location);
  glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, pos));
  glEnableVertexAttribArray(vcol_location);
  glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, col));

  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

  while (!glfwWindowShouldClose(window)) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    const float ratio = width / (float)height;

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    util::tick();
    std::cout << "FPS: " << util::getFps() << std::endl;

    mat4x4 m, p, mvp;
    mat4x4_identity(m);
    mat4x4_rotate_Z(m, m, (float)glfwGetTime());
    mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    mat4x4_mul(mvp, p, m);

    glUseProgram(program);
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat *)&mvp);
    glBindVertexArray(vertex_array);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
