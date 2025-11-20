#include <string>
#include <glad.h>
#include "../util/assets.h"
#include "shader.h"
#include <iostream>

const GLuint compileShader(int shaderType, std::string path)
{
	int success;
	char infoLog[512];
	const GLuint shader = glCreateShader(shaderType);
  std::string shaderText = readFile(path);
  const char *shaderPointer = shaderText.c_str();
  glShaderSource(shader, 1, &shaderPointer, NULL);
  glCompileShader(shader);
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if(!success)
  {
 		glGetShaderInfoLog(shader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  return shader;
}

const GLuint createBaseProgram()
{
	int success;
	char infoLog[512];
	const GLuint vertex_shader = compileShader(GL_VERTEX_SHADER, "shaders/base.vert");
  const GLuint fragment_shader = compileShader(GL_FRAGMENT_SHADER, "shaders/base.frag");
	const GLuint program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if(!success)
  {
      glGetProgramInfoLog(program, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }
  glAttachShader(program, fragment_shader);
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if(!success)
  {
      glGetProgramInfoLog(program, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }
  glLinkProgram(program);
  return program;
}
