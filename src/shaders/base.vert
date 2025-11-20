#version 440 core
uniform mat4 MVP;
in vec2 vPos;
in vec3 vCol;
in vec2 vTexCoord;

out vec3 color;
out vec2 texCoord;

void main()
{
  gl_Position = MVP * vec4(vPos, 0.0, 1.0);
  color = vCol;
  texCoord = vTexCoord;
}
