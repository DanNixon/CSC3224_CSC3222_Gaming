#version 330 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

//uniform float maxHeight;

in vec3 position;
in vec2 texCoord;
in vec4 colour;

out Vertex
{
  vec2 texCoord;
  vec4 colour;
} OUT;

void main(void)
{
  gl_Position = (projMatrix * viewMatrix * modelMatrix) * vec4(position, 1.0);
	
  OUT.texCoord = vec2(position.y, 0);
	
	float maxHeight = 0.1;
	
	vec4 hmCol = vec4(0, 0, 0, 1);
	if(position.y < 0.0)
		hmCol.r = position.y * maxHeight;
	else
		hmCol.g = position.y * maxHeight;
	
  OUT.colour = hmCol;
}
