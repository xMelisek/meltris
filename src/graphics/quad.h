#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Quad {
  const unsigned int indices[6] = {0, 1, 3, 1, 2, 3};
  glm::vec2 vertices[4];
  glm::vec3 colors[4];
  glm::vec2 texCoords[4];

public:
	Quad();
	Quad(glm::vec2 pos, glm::vec2 size, glm::vec3 color);
  GLuint VBO, VAO, EBO, program, texture;
  GLint mvpLoc, vposLoc, vcolLoc, vTexCoordLoc;
  float scale = 1.0f;
  void draw();
};
