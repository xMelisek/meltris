#include <glad.h>
#include "quad.h"
#include <glm/ext/matrix_transform.hpp>
#include "shader.h"
#include <glm/glm.hpp>

Quad::Quad(glm::vec2 pos, glm::vec2 size, glm::vec3 color) {
  vertices[0] = {pos.x - size.x / 2.0f, pos.y + size.y / 2.0f};
  vertices[1] = {pos.x + size.x / 2.0f, pos.y + size.y / 2.0f};
  vertices[2] = {pos.x + size.x / 2.0f, pos.y - size.y / 2.0f};
  vertices[3] = {pos.x - size.x / 2.0f, pos.y - size.y / 2.0f};
  colors[0] = color;
  colors[1] = color;
  colors[2] = color;
  colors[3] = color;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), &colors);

  program = createBaseProgram();

  mvpLoc = glGetUniformLocation(program, "MVP");
  vposLoc = glGetAttribLocation(program, "vPos");
  vcolLoc = glGetAttribLocation(program, "vCol");
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glEnableVertexAttribArray(vposLoc);
  glVertexAttribPointer(vposLoc, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);
  glEnableVertexAttribArray(vcolLoc);
  glVertexAttribPointer(vcolLoc, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)(sizeof(vertices)));

  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);
}

void Quad::draw() {
  glm::mat4 mvp = glm::mat4(1.0f);
  mvp = glm::scale(mvp, glm::vec3(scale));

  glUseProgram(program);
  glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, (const GLfloat *)&mvp);
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
