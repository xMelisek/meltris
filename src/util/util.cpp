#include "util.h"
#include <GLFW/glfw3.h>

namespace util {
double prevTime;
double delta;
double fps;

double getDelta() { return delta; }
double getFps() { return fps; }

void init() { prevTime = glfwGetTime(); }

void tick() {
  delta = glfwGetTime() - prevTime;
  fps = 1.0 / delta;
  prevTime = glfwGetTime();
}
} // namespace util
