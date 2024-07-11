#version 460 core

out vec4 fragColor;
in vec2 textureCoordinate;
uniform sampler2D textureSampler;

void main()
{
	// fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	fragColor = texture(textureSampler, textureCoordinate);
}