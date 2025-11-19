#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Quad {
  const unsigned int indices[6] = {0, 1, 3, 1, 2, 3};
  glm::vec2 vertices[4];
  glm::vec3 colors[4];

public:
	Quad();
	Quad(glm::vec2 pos, glm::vec2 size, glm::vec3 color);
  GLuint VBO, VAO, EBO, program;
  GLint mvpLoc, vposLoc, vcolLoc;
  float scale = 1.0f;
  void draw();
};
