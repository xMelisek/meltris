#include "../../include/glad.h"
#include "glm/ext/vector_float2.hpp"
#include "util.h"

namespace util {
double prevTime;
double delta;
double fps;
glm::vec2 cursorPos = glm::vec2(0.0f);
double getDelta() { return delta; }
double getFps() { return fps; }

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

static void cursor_position_callback(GLFWwindow *window, double xpos,
                                     double ypos) {
       cursorPos = glm::vec2(xpos, ypos);
}

glm::vec2 getCursor() {
	return cursorPos;
}

void init(GLFWwindow *window) {
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, cursor_position_callback);
  prevTime = glfwGetTime();

  glfwMakeContextCurrent(window);
  gladLoadGL(glfwGetProcAddress);
  glfwSwapInterval(1);
}

void tick() {
  delta = glfwGetTime() - prevTime;
  fps = 1.0 / delta;
  prevTime = glfwGetTime();
}
} // namespace util
