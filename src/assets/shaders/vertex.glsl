#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 transform;

void main()
{
  gl_Position = projectionMatrix * viewMatrix * (transform * modelMatrix) * position;
}