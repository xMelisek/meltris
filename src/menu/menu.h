#pragma once
#include "../graphics/quad.h"
#include <GLFW/glfw3.h>
#include <memory>
class Menu {
	std::unique_ptr<Quad> quad, quad2;
public:
  void init();
  void draw(GLFWwindow *window);
};
