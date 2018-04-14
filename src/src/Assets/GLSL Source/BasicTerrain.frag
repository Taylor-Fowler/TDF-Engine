#version 460
const int TEXTURE_COUNT = 3;


uniform float minimumHeight;
uniform float heightRange;
//uniform sampler2D allTextures[TEXTURE_COUNT];
uniform sampler2D grass;
uniform sampler2D dirt;
uniform sampler2D gravel;


in vec4 Colour;
in float y;
in vec2 uv;
out vec4 FinalColour;

void main(void)
{
    float percentage = abs(y - minimumHeight) / heightRange;
    int repeat = 32;
    int grassRepeat = 48;
    if(percentage <= 0.25)
    {
        // 0, 2
        //FinalColour = Colour * mix(texture(allTextures[0], uv), texture(allTextures[2], uv), percentage);
        FinalColour = Colour * mix(texture(gravel, uv * repeat), texture(dirt, uv * repeat), percentage * 4);
    }
    else
    {
        // 1, 2
        //FinalColour = Colour * mix(texture(allTextures[1], uv), texture(allTextures[2], uv), percentage);
        FinalColour = Colour * mix(texture(dirt, uv * repeat), texture(grass, uv * grassRepeat), (percentage - 0.25) / 0.75);
    }
}
