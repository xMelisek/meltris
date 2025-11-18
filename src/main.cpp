#include "engine.h"

int main(void) {
	init();
}



  // glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

  // float lrp = 1.0f;
  // while (!glfwWindowShouldClose(window)) {
  //   int width, height;
  //   glfwGetFramebufferSize(window, &width, &height);
  //   const float ratio = width / (float)height;
  //   bool selected = false;
  //   glm::vec2 ndcMousePos = (glm::vec2(util::getCursor().x / (float)width, util::getCursor().y / (float)height) - 0.5f) * 2.0f;
  //   if(ndcMousePos.x > vertices[0].pos.x && ndcMousePos.x < vertices[1].pos.x && ndcMousePos.y < vertices[0].pos.y && ndcMousePos.y > vertices[3].pos.y)
  //       selected = true;

  //   glViewport(0, 0, width, height);
  //   glClear(GL_COLOR_BUFFER_BIT);

  //   util::tick();
  //   std::cout << "FPS: " << round(util::getFps()) << std::endl;





  //   glfwSwapBuffers(window);
  //   glfwPollEvents();
  // }
// }
