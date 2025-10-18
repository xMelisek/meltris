#include <GLFW/glfw3.h>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	std::cout << "Position: " << xpos << "," << ypos << std::endl;
}

int main() {
  GLFWwindow *window;

  if (!glfwInit()) {
    perror("GLFW not initialized!");
    exit(EXIT_FAILURE);
  }

  window = glfwCreateWindow(1280, 720, "Meltris", NULL, NULL);

  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, cursor_position_callback);

  glfwMakeContextCurrent(window);
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
