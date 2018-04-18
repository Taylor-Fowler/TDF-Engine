#version 460
//https://www.keithlantz.net/2011/10/rendering-a-skybox-using-a-cube-map-with-opengl-and-glsl/
in vec3 texCoord;

uniform samplerCube skyboxMap;

out vec4 FinalColour;
 
void main (void) {
    FinalColour = texture(skyboxMap, texCoord);
}