#version 460

////////////////////////////////////
////	VERTEX ATTRIBS
////////////////////////////////////
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textureCoordinate;

////////////////////////////////////
////	UNIFORMS
////////////////////////////////////
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 modelViewMatrix;


uniform vec3 ambientMaterial;



out vec4 Colour;
out float y;
out vec2 uv;


void main(void)
{
  uv = textureCoordinate;
  y = vertex.y;
  Colour = vec4(ambientMaterial, 1);
  gl_Position = projectionMatrix * modelViewMatrix * vec4(vertex, 1);
}
