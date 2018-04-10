#version 460

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
  vec3 Direction;
  vec3 Diffuse;
};

struct POINT_LIGHT
{
  int On;
  vec3 Position;
  vec3 Diffuse;
  vec3 Specular;
};

struct SPOT_LIGHT
{
  int On;
  vec3 Position;
  vec3 Diffuse;
  vec3 Specular;
  vec3 Direction;
  float Cutoff;
  float Attenuation;
};

struct VERTEX_OUT
{
  vec4 Colour;
  vec4 Position;
  vec3 Normal;
  vec2 TextureCoordinate;
  vec3 TextureCoordinateCubeMap;
  vec4 ShadowCoordinate;
};

////////////////////////////////////
////	UNIFORM BUFFER OBJECTS
////////////////////////////////////
//layout (std140) uniform lights
//{
//	vec3 AmbientLight;
//	DIRECTIONAL_LIGHT DirectionalLights[MAX_DIRECTIONAL_LIGHTS];
//	SPOT_LIGHT SpotLights[MAX_SPOT_LIGHTS];
//	POINT_LIGHT PointLights[MAX_POINT_LIGHTS];
//};

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

uniform vec3 ambientLight;
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
  vertexOut.Colour = vec4(0, 0, 0, 1) + ApplyAmbientLight(ambientMaterial);
  vertexOut.ShadowCoordinate = shadowMatrix * modelMatrix * vec4(vertex + normal * 0.1, 1);

  gl_Position = projectionMatrix * vertexOut.Position;
}




vec4 ApplyAmbientLight(vec3 colour)
{
  return vec4(ambientLight * colour, 1);
}
