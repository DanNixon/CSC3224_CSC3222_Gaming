#version 330 core

uniform sampler2D tabletopTex;

in Vertex
{
  vec2 texCoord;
  vec4 colour;
} IN;

out vec4 fragCol;

void main(void)
{
  fragCol = texture(tabletopTex, IN.texCoord);
}