#version 460

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 textureCoordinate;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

void main(void)
{
  gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 1.0);
  //gl_Position = vec4(vertex, 1.0);
}
