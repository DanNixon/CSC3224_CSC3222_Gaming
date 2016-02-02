#version 330 core

uniform float animPosition;
uniform sampler2D objectTexture;

in Vertex
{
  vec2 texCoord;
  vec4 colour;
} IN;

out vec4 fragCol;

void main(void)
{
  fragCol = IN.colour;
}
