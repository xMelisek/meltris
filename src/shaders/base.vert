#version 330
uniform mat4 MVP;
in vec2 vPos;
in vec3 vCol;

out vec3 color;

void main()
{
  gl_Position = MVP * vec4(vPos, 0.0, 1.0);
  color = vCol;
}
