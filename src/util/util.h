#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
namespace util {
	double getDelta();
	double getFps();
	glm::vec2 getCursor();
	void init(GLFWwindow* window);
	void tick();
}
