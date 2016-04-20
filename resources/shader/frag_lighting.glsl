#version 330 core

uniform sampler2D tex;

uniform vec3 cameraPos;

uniform vec4 ambientColour;
uniform vec4 diffuseColour;
uniform vec4 specularColour;
uniform float ambientStrength;
uniform float shininess;
uniform float shininessStrength;

uniform vec3 light_sun_position;
uniform float light_sun_radius;
uniform float light_sun_intensity;

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
  vec3 incident = normalize(light_sun_position - IN.worldPos);
  vec3 viewDir = normalize(cameraPos - IN.worldPos);
  vec3 halfDir = normalize(incident + viewDir);

  float dist = length(light_sun_position - IN.worldPos);
  float atten = 1.0 - clamp(dist / light_sun_radius, 0.0 , 1.0);
  float lambert = max(0.0, dot(incident, IN.normal));

  float rFactor = max(0.0, dot(halfDir, IN.normal));
  float sFactor = pow(rFactor, shininess) * shininessStrength;

  vec4 texCol = texture(tex, IN.texCoord);

  vec4 ambient = vec4(texCol.rgb, 1.0) * ambientColour * ambientStrength;
  vec4 diffuse = vec4(texCol.rgb, 1.0) * diffuseColour * lambert * atten;
  vec4 specular = specularColour * sFactor * atten * light_sun_intensity;
	
	fragCol = vec4(ambient.rgb + diffuse.rgb + specular.rgb, texCol.a);
}