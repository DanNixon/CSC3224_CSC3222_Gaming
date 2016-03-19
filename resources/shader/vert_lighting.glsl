#version 330 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

in vec3 position;
in vec2 texCoord;
in vec4 colour;
in vec3 normal;

out Vertex
{
  vec2 texCoord;
  vec4 colour;
	vec3 worldPos;
	vec3 normal;
} OUT;

void main(void)
{
	vec4 worldPos = modelMatrix * vec4(position, 1.0);
	
  OUT.texCoord = texCoord;
  OUT.colour = colour;
	OUT.worldPos = worldPos.xyz;
	
	mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
  OUT.normal = normalize(normalMatrix * normalize(normal));
	
	gl_Position = projMatrix * viewMatrix * worldPos;
}
