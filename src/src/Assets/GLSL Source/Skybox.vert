#version 460
//https://www.keithlantz.net/2011/10/rendering-a-skybox-using-a-cube-map-with-opengl-and-glsl/
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textureCoordinate;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 texCoord;

 
void main() {
    gl_Position = projectionMatrix * viewMatrix * vec4(vertex, 1.0);
    texCoord = vertex;
}