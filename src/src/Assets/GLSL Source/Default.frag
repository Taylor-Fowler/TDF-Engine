#version 460

uniform vec3 vColour;

out vec4 finalColour;

void main(void)
{
  finalColour = vec4(vColour, 1.0);
}
