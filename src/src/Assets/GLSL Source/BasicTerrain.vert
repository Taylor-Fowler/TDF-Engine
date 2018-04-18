#version 460

////////////////////////////////////
////	VERTEX ATTRIBS
////////////////////////////////////
layout (location = 0) in vec4 vertex;
layout (location = 1) in vec4 normal;
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
out vec3 vertexNormal;


void main(void)
{
  uv = textureCoordinate;
  y = vertex.y;
  vertexNormal = mat3(viewMatrix) * normal.xyz;
  Colour = vec4(ambientMaterial, 1);
  gl_Position = projectionMatrix * viewMatrix * vertex;
}
