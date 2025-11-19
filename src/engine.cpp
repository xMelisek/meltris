#define GLAD_GL_IMPLEMENTATION
#include <glad.h>
#include <GLFW/glfw3.h>
#include "engine.h"

#include "util/math.h"

#include "menu/menu.h"

#include <iostream>

namespace engine {
	double prevTime;
	double delta;
	double fps, rawfps = 0.;
	glm::vec2 cursorPos = glm::vec2(0.0f);
	double getDelta() { return delta; }
	double getFps() { return rawfps; }
	glm::vec2 getCursor() { return cursorPos; }
}

GLFWwindow *window;
Menu menu;

static void errorCallback(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

static void cursorCallback(GLFWwindow *window, double xpos, double ypos) {
  engine::cursorPos = glm::vec2(xpos, ypos);
}

//TODO: Shove this into its own input class
static void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

void loop();
void finish();
void tick();

void init() {
  glfwSetErrorCallback(errorCallback);
  if (!glfwInit()) {
    perror("GLFW not initialized!");
    exit(EXIT_FAILURE);
  }
  window = glfwCreateWindow(1280, 720, "Meltris", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwSetKeyCallback(window, keyCallback);
  glfwSetCursorPosCallback(window, cursorCallback);
  engine::prevTime = glfwGetTime();

  glfwMakeContextCurrent(window);
  gladLoadGL(glfwGetProcAddress);
  glfwSwapInterval(1); // Enable VSync
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  menu.init(); // Temp hardcode
  loop();
}

void loop() {
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    tick();
    menu.draw(window); // Temp hardcode
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  finish();
}

void tick() {
  engine::delta = glfwGetTime() - engine::prevTime;
  engine::rawfps = 1.0 / engine::delta;
  engine::fps = math::lerp(engine::fps, engine::rawfps, 0.2f * engine::delta * 60.f);
  engine::prevTime = glfwGetTime();
  std::cout << "FPS: " << round(engine::fps) << std::endl;
}

void finish() {
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
