#version 330 core

uniform sampler2D tex;

uniform vec3 cameraPos;

uniform vec4 ambientColour;
uniform vec4 diffuseColour;
uniform vec4 specularColour;
uniform float ambientStrength;
uniform float shininess;
uniform float shininessStrength;

in Vertex
{
  vec2 texCoord;
  vec4 colour;
	vec3 worldPos;
	vec3 normal;
} IN;

out vec4 fragCol;

void main(void)
{
	vec3 lightPos = vec3(0, -500, 0);
	float lightRadius = 10000.0;

  vec3 incident = normalize(lightPos - IN.worldPos);
  vec3 viewDir = normalize(cameraPos - IN.worldPos);
  vec3 halfDir = normalize(incident + viewDir);

  float dist = length(lightPos - IN.worldPos);
  float atten = 1.0 - clamp(dist / lightRadius, 0.0 , 1.0);
  float lambert = max(0.0, dot(incident, IN.normal));

  float rFactor = max(0.0, dot(halfDir, IN.normal));
  float sFactor = pow(rFactor, shininess) * shininessStrength;

  vec4 texCol = texture(tex, IN.texCoord);

  vec4 ambient = vec4(texCol.rgb, 1.0) * ambientColour * ambientStrength;
  vec4 diffuse = vec4(texCol.rgb, 1.0) * diffuseColour * lambert * atten;
  vec4 specular = specularColour * sFactor * atten;
	
	fragCol = vec4(ambient.rgb + diffuse.rgb + specular.rgb, texCol.a);
	//fragCol = ambientColour;
}