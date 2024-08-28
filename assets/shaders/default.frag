#version 460 core

out vec4 fragColor;
in vec2 textureCoordinate;
in vec3 normal;
in vec3 fragmentWorldSpacePosition;

uniform sampler2D textureSampler;
uniform vec3 lightPosition;

const vec4 lightColor = vec4(1, 1, 1, 1);
const float lightPower = 5;
const vec4 ambient = vec4(1, 1, 1, 1);

void main()
{
	vec4 textureColor = texture(textureSampler, textureCoordinate);

	vec3 lightDirection = normalize(lightPosition - fragmentWorldSpacePosition);
	float diffuseStrength = max(dot(normalize(normal), lightDirection), 0);
	vec4 diffuse = lightColor * diffuseStrength * lightPower;
	
	fragColor = textureColor * (diffuse + ambient);
}