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
	
	float inverseHeightFactor = 1.0 / 10.0;
	float factor = position.y * inverseHeightFactor;
	
  OUT.texCoord = vec2(0.5 + (0.5 * factor), 0);
	
	vec4 hmCol = vec4(0, 0, 0, 1);
	if(position.y < 0.0)
		hmCol.r = factor;
	else
		hmCol.g = factor;
	
  OUT.colour = hmCol;
}
