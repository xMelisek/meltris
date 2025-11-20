#include <glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>
#include "quad.h"
#include <glm/ext/matrix_transform.hpp>
#include "shader.h"
#include <glm/glm.hpp>
#include <string>
#include "../util/assets.h"

Quad::Quad(glm::vec2 pos, glm::vec2 size, glm::vec3 color) {
  vertices[0] = {pos.x - size.x / 2.0f, pos.y + size.y / 2.0f};
  vertices[1] = {pos.x + size.x / 2.0f, pos.y + size.y / 2.0f};
  vertices[2] = {pos.x + size.x / 2.0f, pos.y - size.y / 2.0f};
  vertices[3] = {pos.x - size.x / 2.0f, pos.y - size.y / 2.0f};
  colors[0] = color;
  colors[1] = color;
  colors[2] = color;
  colors[3] = color;
  texCoords[0] = glm::vec2(0.0f, 1.0f);
  texCoords[1] = glm::vec2(1.0f, 1.0f);
  texCoords[2] = glm::vec2(1.0f, 0.0f);
  texCoords[3] = glm::vec2(0.0f, 0.0f);
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors) + sizeof(texCoords), NULL, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), &colors);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), sizeof(texCoords), &texCoords);

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  // set the texture wrapping/filtering options (on the currently bound texture object)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // load and generate the texture
  int width, height, nrChannels;
  std::string path = getExecDir() + "assets/textures/doidsmile.png";
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
  if (data)
  {
  	std::cout << data << std::endl;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);

  program = createBaseProgram();

  mvpLoc = glGetUniformLocation(program, "MVP");
  vposLoc = glGetAttribLocation(program, "vPos");
  vcolLoc = glGetAttribLocation(program, "vCol");
  vTexCoordLoc = glGetAttribLocation(program, "vTexCoord");
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glEnableVertexAttribArray(vposLoc);
  glVertexAttribPointer(vposLoc, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);
  glEnableVertexAttribArray(vcolLoc);
  glVertexAttribPointer(vcolLoc, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)(sizeof(vertices)));
  glEnableVertexAttribArray(vTexCoordLoc);
  glVertexAttribPointer(vTexCoordLoc, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(sizeof(vertices) + sizeof(colors)));


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
  glBindTexture(GL_TEXTURE_2D, texture);
  glUniform1i(glGetUniformLocation(program, "vTex"), 0);
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
