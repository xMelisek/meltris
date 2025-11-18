#include "../../include/glad.h"
#include <GLFW/glfw3.h>
#include "../engine.h"
#include "../util/geometry.h"
#include "../util/math.h"
#include "../util/shader.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>

namespace menu {
// Test quad, temp hardcode
const Vertex vertices[4] = {
    {{-0.5f, 0.5f}, {0.05f, 0.05f, 0.05f}},
    {{0.5f, 0.5f}, {0.05f, 0.05f, 0.05f}},
    {{0.5f, -0.5f}, {0.05f, 0.05f, 0.05f}},
    {{-0.5f, -0.5f}, {0.05f, 0.05f, 0.05f}},
};
unsigned int indices[] = {0, 1, 3, 1, 2, 3};

GLuint VBO, VAO, EBO, program;
GLint mvpLoc, vposLoc, vcolLoc;

bool selected = false;
float lrp = 1.0f;

void init() {
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  program = createBaseProgram();

  mvpLoc = glGetUniformLocation(program, "MVP");
  vposLoc = glGetAttribLocation(program, "vPos");
  vcolLoc = glGetAttribLocation(program, "vCol");
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glEnableVertexAttribArray(vposLoc);
  glVertexAttribPointer(vposLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, pos));
  glEnableVertexAttribArray(vcolLoc);
  glVertexAttribPointer(vcolLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, col));

  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);
}

void draw(GLFWwindow* window) {
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  bool selected = false;
  glm::vec2 ndcMousePos = (glm::vec2(engine::getCursor().x / (float)width, engine::getCursor().y / (float)height) - 0.5f) * 2.0f;
  if(ndcMousePos.x > vertices[0].pos.x && ndcMousePos.x < vertices[1].pos.x && ndcMousePos.y < vertices[0].pos.y && ndcMousePos.y > vertices[3].pos.y)
      selected = true;
  lrp = math::lerp(lrp, selected ? 1.2f : 1.0f, 0.2f * engine::getDelta() * 60.f);

  glm::mat4 mvp = glm::mat4(1.0f);
  mvp = glm::scale(mvp, glm::vec3(lrp));

  glUseProgram(program);
  glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, (const GLfloat *)&mvp);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
} // namespace menu
