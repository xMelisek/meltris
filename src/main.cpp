#define GLAD_GL_IMPLEMENTATION
#include "../include/glad.h"
#include <GLFW/glfw3.h>
#include "util/util.h"

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "util/shader.h"
#include "util/math.h"
#include <iostream>

struct Vertex {
  glm::vec2 pos;
  glm::vec3 col;
};

static const Vertex vertices[4] = {{{-0.5f, 0.5f}, {0.05f, 0.05f, 0.05f}},
                                   {{0.5f, 0.5f}, {0.05f, 0.05f, 0.05f}},
                                   {{0.5f, -0.5f}, {0.05f, 0.05f, 0.05f}},
                                   {{-0.5f, -0.5f}, {0.05f, 0.05f, 0.05f}}};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};

static void error_callback(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

int main(void) {
  glfwSetErrorCallback(error_callback);
  GLFWwindow *window;
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
  util::init(window);

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

  GLuint EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

  float lrp = 1.0f;
  while (!glfwWindowShouldClose(window)) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    const float ratio = width / (float)height;
    bool selected = false;
    glm::vec2 ndcMousePos = (glm::vec2(util::getCursor().x / (float)width, util::getCursor().y / (float)height) - 0.5f) * 2.0f;
    if(ndcMousePos.x > vertices[0].pos.x && ndcMousePos.x < vertices[1].pos.x && ndcMousePos.y < vertices[0].pos.y && ndcMousePos.y > vertices[3].pos.y)
        selected = true;

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    util::tick();
    std::cout << "FPS: " << round(util::getFps()) << std::endl;

    glm::mat4 mvp = glm::mat4(1.0f);
    lrp = math::lerp(lrp, selected ? 1.2f : 1.0f, 0.2f * util::getDelta() * 60.0f);
    mvp = glm::scale(mvp, glm::vec3(lrp));

    glUseProgram(program);
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat *)&mvp);
    glBindVertexArray(vertex_array);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
