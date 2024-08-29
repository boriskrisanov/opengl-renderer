#version 460 core

out vec4 fragColor;
in vec2 textureCoordinate;
in vec3 normal;
in vec3 fragmentWorldSpacePosition;

uniform sampler2D textureSampler;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;

const vec4 lightColor = vec4(1, 1, 1, 1);
const float lightPower = 2.5;
const vec4 ambient = vec4(1, 1, 1, 1);
const float specularStrength = 0.5;

void main()
{
	vec4 textureColor = texture(textureSampler, textureCoordinate);

	vec3 lightDirection = normalize(lightPosition - fragmentWorldSpacePosition);
	float diffuseStrength = max(dot(normalize(normal), lightDirection), 0);
	vec4 diffuse = lightColor * diffuseStrength * lightPower;

	vec3 viewDirection = normalize(cameraPosition - fragmentWorldSpacePosition);
	vec3 reflectedRay = reflect(-lightDirection, normalize(normal));
	
	float specularValue = pow(max(dot(viewDirection, reflectedRay), 0), 32);
	vec4 specular = specularStrength * specularValue * textureColor;

	fragColor = textureColor * (diffuse + ambient +specular);
}