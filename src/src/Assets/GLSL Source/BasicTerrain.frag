#version 460

#pragma REGION LIGHTING
///////////////////////////////////
////    CONSTANTS
///////////////////////////////////
const int MAX_DIRECTIONAL_LIGHTS = 10;
const int MAX_POINT_LIGHTS = 10;
const int MAX_SPOT_LIGHTS = 10;
const int MAX_TOTAL_LIGHTS = MAX_DIRECTIONAL_LIGHTS + MAX_POINT_LIGHTS + MAX_SPOT_LIGHTS;
const float QUADRATIC_ATTENTUATION = 0.09f;

///////////////////////////////////
////    STRUCTS
///////////////////////////////////
struct DIRECTIONAL_LIGHT
{
    int On;
    vec4 Direction;
    vec4 Diffuse;
};

struct POINT_LIGHT
{
    int On;
    vec4 Position;
    vec4 Diffuse;
    vec4 Specular;
};

struct SPOT_LIGHT
{
    int On;
    vec4 Position;
    vec4 Diffuse;
    vec4 Specular;
    vec4 Direction;
    float Cutoff;
    float Attenuation;
};

////////////////////////////////////
////	UNIFORM BUFFER OBJECTS
////////////////////////////////////
layout (std140) uniform lights
{
	vec4 AmbientLight;
	DIRECTIONAL_LIGHT DirectionalLights[MAX_DIRECTIONAL_LIGHTS];
	SPOT_LIGHT SpotLights[MAX_SPOT_LIGHTS];
	POINT_LIGHT PointLights[MAX_POINT_LIGHTS];
};
#pragma ENDREGION

#pragma REGION VERTEX_OUT
struct VERTEX_OUT
{
    vec4 Colour;
    vec4 Position;
    vec3 Normal;
    vec2 TextureCoordinate;
    float y;
};
#pragma ENDREGION


////////////////////////////////////
////	UNIFORMS
////////////////////////////////////
uniform mat4 viewMatrix;
uniform float minimumHeight;
uniform float heightRange;

uniform sampler2D dirt;
uniform sampler2D dirtGrass;
uniform sampler2D grassLong;
uniform sampler2D rockyDirt;
uniform sampler2D dryGrass;

///////////////////////////////////
////    FORWARD DECLARATIONS
///////////////////////////////////
vec4 ApplyPointLight(POINT_LIGHT light);
vec4 ApplySpotLight(SPOT_LIGHT light);
vec4 ApplyDirectionalLight(DIRECTIONAL_LIGHT light);

in VERTEX_OUT vertexOut;
out vec4 FinalColour;

vec3 specularMaterial = vec3(1, 1, 1);
vec3 diffuseMaterial = vec3(1, 1, 1);
float shininessMaterial = 0.1;


void main(void)
{
    float percentage = (vertexOut.y == minimumHeight) ? 0.0 : abs((vertexOut.y-minimumHeight) / heightRange);

    FinalColour = vertexOut.Colour;

    for(int i = 0; i < MAX_DIRECTIONAL_LIGHTS; i++) 
    {
		FinalColour += ApplyDirectionalLight(DirectionalLights[i]) * DirectionalLights[i].On;
	}

	for(int i = 0; i < MAX_POINT_LIGHTS; i++) 
    {
		FinalColour += ApplyPointLight(PointLights[i]) * PointLights[i].On;
	}

	for(int i = 0; i < MAX_SPOT_LIGHTS; i++) 
    {
		FinalColour += ApplySpotLight(SpotLights[i]) * SpotLights[i].On;
	}


    if(percentage < 0.04)
    {
        FinalColour *= mix(texture(dirt, vertexOut.TextureCoordinate), texture(dirtGrass, vertexOut.TextureCoordinate), percentage / 0.04);
    }
    else if(percentage < 0.16)
    {
        // divided by 0.09 to make it sway towards tex2
        FinalColour *= mix(texture(dirtGrass, vertexOut.TextureCoordinate), texture(grassLong, vertexOut.TextureCoordinate), clamp((percentage - 0.04) / 0.09, 0.0, 1.0));
    }
    else if(percentage < 0.30)
    {
        FinalColour *= mix(texture(grassLong, vertexOut.TextureCoordinate), texture(dryGrass, vertexOut.TextureCoordinate), (percentage - 0.16) / 0.14);
    }
    else
    {
        FinalColour *= texture(dryGrass, vertexOut.TextureCoordinate);
    }
}

vec4 ApplyDirectionalLight(DIRECTIONAL_LIGHT light)
{
    //vec3 L = normalize(mat3(viewMatrix) * -normalize(vec3(0.5, -1.0, 0.5))); // Calculate the light direction in view space
    vec3 L = normalize(mat3(viewMatrix) * -normalize(light.Direction.xyz)); // Calculate the light direction in view space

    float NdotL = max(dot(vertexOut.Normal, L), 0);

    return light.Diffuse * vec4(diffuseMaterial, 1) * NdotL;
}


vec4 ApplyPointLight(POINT_LIGHT light)
{
    vec4 Colour = vec4(0, 0, 0, 1);
    vec3 L = (viewMatrix * light.Position).xyz; // Calculate light position in view space
    L -= vertexOut.Position.xyz; // Find the direction from vertex to light
    L = normalize(L); // Direction should be normalized

    float NdotL = max(dot(vertexOut.Normal, L), 0);
    Colour += light.Diffuse * vec4(diffuseMaterial, 1) * NdotL;


    vec3 V = normalize(-vertexOut.Position.xyz); // Calculate direction of camera from vertex
    vec3 R = reflect(-L, vertexOut.Normal);

    float RdotV = max(dot(R, V), 0);

    if(RdotV != 0 && NdotL != 0)
    {
        Colour += vec4(specularMaterial * light.Specular.xyz * pow(RdotV, shininessMaterial), 1);
    }
    return Colour;
}

vec4 ApplySpotLight(SPOT_LIGHT light)
{
    vec4 Colour = vec4(0, 0, 0, 1);
    vec3 L = (viewMatrix * light.Position).xyz; // Calculate light position in view space
    L -= vertexOut.Position.xyz; // Find the direction from vertex to light
    L = normalize(L); // Direction should be normalized

    float NdotL = max(dot(vertexOut.Normal, L), 0);
    Colour += light.Diffuse * vec4(diffuseMaterial, 1) * NdotL;


    vec3 V = normalize(-vertexOut.Position.xyz); // Calculate direction of camera from vertex
    vec3 R = reflect(-L, vertexOut.Normal);

    float RdotV = max(dot(R, V), 0);

    if(RdotV != 0 && NdotL != 0)
        Colour += vec4(specularMaterial * light.Specular.xyz * pow(RdotV, shininessMaterial), 1);

    // Spot Factor calculation below
    vec3 D = normalize(mat3(viewMatrix) * light.Direction.xyz);
    float s = dot(-L, D);
    float alpha = acos(s);
    float deg = radians(clamp(light.Cutoff, 0, 90)); // Convert cutoff to degrees and clamp between 0-90

    float spotFactor = 0;
    if(alpha <= deg) 
    {
        spotFactor = pow(s, alpha);
    }

    // Attenuation factor below
    float dist = length(viewMatrix * light.Position - vertexOut.Position);
    float att = 1 / (QUADRATIC_ATTENTUATION * dist * dist);

    return Colour * spotFactor * att;
}