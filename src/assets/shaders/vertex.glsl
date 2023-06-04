#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 _textureCoordinate;

out vec2 textureCoordinate;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 transform;

void main()
{
  gl_Position = projectionMatrix * viewMatrix * (transform) * position;
  textureCoordinate = _textureCoordinate;
}