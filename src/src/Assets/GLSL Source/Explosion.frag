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
    vec3 TextureCoordinateCubeMap;
    vec4 ShadowCoordinate;
};
#pragma ENDREGION


////////////////////////////////////
////	UNIFORMS
////////////////////////////////////
uniform mat4 viewMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 shadowMatrix;


uniform sampler2D texture0;
uniform samplerCube reflectionCubeMap;
uniform sampler2DShadow shadowMap;

uniform vec3 diffuseMaterial;
uniform vec3 specularMaterial;
uniform float shininessMaterial;
uniform float reflectivityMaterial;

///////////////////////////////////
////    FORWARD DECLARATIONS
///////////////////////////////////
vec4 ApplyPointLight(POINT_LIGHT light);
vec4 ApplySpotLight(SPOT_LIGHT light);
vec4 ApplyDirectionalLight(DIRECTIONAL_LIGHT light);

in VERTEX_OUT GeomResult;
out vec4 FinalColour;

void main(void)
{
	FinalColour = GeomResult.Colour;

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


	FinalColour = mix(FinalColour * texture(texture0, GeomResult.TextureCoordinate.st),
					texture(reflectionCubeMap, GeomResult.TextureCoordinateCubeMap), reflectivityMaterial);

}


vec4 ApplyDirectionalLight(DIRECTIONAL_LIGHT light)
{
    vec3 L = normalize(mat3(viewMatrix) * -light.Direction.xyz); // Calculate the light direction in view space

    float NdotL = max(dot(GeomResult.Normal, L), 0);

    return light.Diffuse * vec4(diffuseMaterial, 1) * NdotL;
}


vec4 ApplyPointLight(POINT_LIGHT light)
{
    vec4 Colour = vec4(0, 0, 0, 1);
    vec3 L = (viewMatrix * light.Position).xyz; // Calculate light position in view space
    L -= GeomResult.Position.xyz; // Find the direction from vertex to light
    L = normalize(L); // Direction should be normalized

    float NdotL = max(dot(GeomResult.Normal, L), 0);
    Colour += light.Diffuse * vec4(diffuseMaterial, 1) * NdotL;


    vec3 V = normalize(-GeomResult.Position.xyz); // Calculate direction of camera from vertex
    vec3 R = reflect(-L, GeomResult.Normal);

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
    L -= GeomResult.Position.xyz; // Find the direction from vertex to light
    L = normalize(L); // Direction should be normalized

    float NdotL = max(dot(GeomResult.Normal, L), 0);
    Colour += light.Diffuse * vec4(diffuseMaterial, 1) * NdotL;


    vec3 V = normalize(-GeomResult.Position.xyz); // Calculate direction of camera from vertex
    vec3 R = reflect(-L, GeomResult.Normal);

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
    float dist = length(viewMatrix * light.Position - GeomResult.Position);
    float att = 1 / (QUADRATIC_ATTENTUATION * dist * dist);

    return Colour * spotFactor * att;
}
