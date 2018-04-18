#version 460
const int TEXTURE_COUNT = 3;

uniform mat4 viewMatrix;
uniform float minimumHeight;
uniform float heightRange;
//uniform sampler2D allTextures[TEXTURE_COUNT];
uniform sampler2D grass;
uniform sampler2D dirt;
uniform sampler2D gravel;

vec4 ApplyDirectionalLight(vec3 direction);

in vec4 Colour;
in float y;
in vec2 uv;
in vec3 vertexNormal;
out vec4 FinalColour;



void main(void)
{
    float percentage = (y == minimumHeight) ? 0.0 : abs((y-minimumHeight) / heightRange);
    int repeat = 1;
    int grassRepeat = 1;
    FinalColour = Colour + ApplyDirectionalLight(normalize(vec3(-0.5, -0.5, -0.5)));

    if(percentage <= 0.25)
    {
        FinalColour *= mix(texture(gravel, uv * repeat), texture(dirt, uv * repeat), percentage * 4);
    }
    else
    {
        FinalColour *= mix(texture(dirt, uv * repeat), texture(grass, uv * grassRepeat), (percentage - 0.25) / 0.75);
    }   
}

vec4 ApplyDirectionalLight(vec3 direction)
{
  vec3 L = normalize(mat3(viewMatrix) * -direction); // Calculate the light direction in view space

  float NdotL = max(dot(vertexNormal, L), 0);

  return vec4(vec3(0.3, 0.6, 0.3) * vec3(1.0, 0.8, 0.6), 1) * NdotL;
}