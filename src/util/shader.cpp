#include <string>
#include <glad.h>
#include "assets.h"
#include "shader.h"

const GLuint compileShader(int shaderType, std::string path)
{
	const GLuint shader = glCreateShader(shaderType);
  std::string shaderText = readFile(path);
  const char *shaderPointer = shaderText.c_str();
  glShaderSource(shader, 1, &shaderPointer, NULL);
  glCompileShader(shader);
  return shader;
}

const GLuint createBaseProgram()
{
	const GLuint vertex_shader = compileShader(GL_VERTEX_SHADER, "shaders/base.vert");
  const GLuint fragment_shader = compileShader(GL_FRAGMENT_SHADER, "shaders/base.frag");
	const GLuint program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);
  return program;
}
