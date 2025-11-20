#version 440 core
in vec3 color;
in vec2 texCoord;

out vec4 fragment;

uniform sampler2D vTex;

void main()
{
  fragment = texture(vTex, texCoord) * vec4(color, 1.0);
}
