#include <glad.h>
#include "menu.h"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <memory>

  bool selected = false;
  float lrp = 1.0f;

  void Menu::init() {
  	quad = std::make_unique<Quad>(glm::vec2(0.0f), glm::vec2(1.0f), glm::vec3(0.15f));
   quad2 = std::make_unique<Quad>(glm::vec2(0.75f), glm::vec2(0.2f), glm::vec3(1.f));
  }

  void Menu::draw(GLFWwindow *window) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    bool selected = false;
    quad->scale = sin(glfwGetTime());
    quad->draw();
    quad2->scale = sin(glfwGetTime());
    quad2->draw();
    // glm::vec2 ndcMousePos = (glm::vec2(engine::getCursor().x / (float)width,
    // engine::getCursor().y / (float)height) - 0.5f) * 2.0f; if(ndcMousePos.x >
    // vertices[0].pos.x && ndcMousePos.x < vertices[1].pos.x && ndcMousePos.y <
    // vertices[0].pos.y && ndcMousePos.y > vertices[3].pos.y)
    //     selected = true;
    // lrp = math::lerp(lrp, selected ? 1.2f : 1.0f, 0.2f * engine::getDelta()
    // * 60.f);
  }
