#version 460

#pragma REGION LIGHTING
///////////////////////////////////
////    CONSTANTS
///////////////////////////////////
const int MAX_DIRECTIONAL_LIGHTS = 10;
const int MAX_POINT_LIGHTS = 10;
const int MAX_SPOT_LIGHTS = 10;
const int MAX_TOTAL_LIGHTS = MAX_DIRECTIONAL_LIGHTS + MAX_POINT_LIGHTS + MAX_SPOT_LIGHTS;

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
////	VERTEX ATTRIBS
////////////////////////////////////
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textureCoordinate;


////////////////////////////////////
////	UNIFORMS
////////////////////////////////////
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 shadowMatrix;

uniform vec3 ambientMaterial;


vec4 ApplyAmbientLight(vec3 colour);

out VERTEX_OUT vertexOut;

void main(void)
{
    vertexOut.TextureCoordinate = textureCoordinate;
    vertexOut.Position = modelViewMatrix * vec4(vertex, 1.0);
    vertexOut.Normal = normalize(mat3(modelViewMatrix) * normal);
    vertexOut.TextureCoordinateCubeMap =  inverse(mat3(viewMatrix)) *
        mix(reflect(vertexOut.Position.xyz, vertexOut.Normal), vertexOut.Normal, 0.2);

    vertexOut.Colour = ApplyAmbientLight(ambientMaterial);
    vertexOut.ShadowCoordinate = shadowMatrix * modelMatrix * vec4(vertex + normal * 0.1, 1);

    gl_Position = projectionMatrix * vertexOut.Position;
}




vec4 ApplyAmbientLight(vec3 colour)
{
    return AmbientLight * vec4(colour, 1);
}
