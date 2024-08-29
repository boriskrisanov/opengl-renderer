#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 _textureCoordinate;
layout(location = 2) in vec3 _normal;

out vec2 textureCoordinate;
out vec3 normal;
out vec3 fragmentWorldSpacePosition;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

void main()
{
  gl_Position = projectionMatrix * viewMatrix * modelMatrix * position;
  fragmentWorldSpacePosition = vec3(modelMatrix * position);
  textureCoordinate = _textureCoordinate;

  // TODO: Do this on the CPU
  // mat3 * vec3 = vec3
  normal = mat3(transpose(inverse(modelMatrix))) * _normal;
}