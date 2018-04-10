#version 460
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
////	UNIFORMS
////////////////////////////////////
uniform mat4 viewMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 shadowMatrix;

uniform DIRECTIONAL_LIGHT directionalLights[MAX_DIRECTIONAL_LIGHTS];
uniform POINT_LIGHT pointLights[MAX_POINT_LIGHTS];
uniform SPOT_LIGHT spotLights[MAX_SPOT_LIGHTS];

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

	for(int i = 0; i < MAX_DIRECTIONAL_LIGHTS; i++) {
		FinalColour += ApplyDirectionalLight(directionalLights[i]) * directionalLights[i].On;
	}

	for(int i = 0; i < MAX_POINT_LIGHTS; i++) {
		FinalColour += ApplyPointLight(pointLights[i]) * pointLights[i].On;
	}

	for(int i = 0; i < MAX_SPOT_LIGHTS; i++) {
		FinalColour += ApplySpotLight(spotLights[i]) * spotLights[i].On;
	}


	FinalColour = mix(FinalColour * texture(texture0, GeomResult.TextureCoordinate.st),
					texture(reflectionCubeMap, GeomResult.TextureCoordinateCubeMap), reflectivityMaterial);

}


vec4 ApplyDirectionalLight(DIRECTIONAL_LIGHT light)
{
  vec3 L = normalize(mat3(viewMatrix) * light.Direction); // Calculate the light direction in view space

  float NdotL = max(dot(GeomResult.Normal, L), 0);

  return vec4(diffuseMaterial * light.Diffuse, 1) * NdotL;
}


vec4 ApplyPointLight(POINT_LIGHT light)
{
  vec4 Colour = vec4(0, 0, 0, 1);
  vec3 L = (viewMatrix * vec4(light.Position, 1)).xyz; // Calculate light position in view space
  L -= GeomResult.Position.xyz; // Find the direction from vertex to light
  L = normalize(L); // Direction should be normalized

  float NdotL = max(dot(GeomResult.Normal, L), 0);
  Colour += vec4(diffuseMaterial * light.Diffuse, 1) * NdotL;


  vec3 V = normalize(-GeomResult.Position.xyz); // Calculate direction of camera from vertex
  vec3 R = reflect(-L, GeomResult.Normal);

  float RdotV = max(dot(R, V), 0);

  if(RdotV != 0 && NdotL != 0)
  {
    Colour += vec4(specularMaterial * light.Specular * pow(RdotV, shininessMaterial), 1);
  }
  return Colour;
}

vec4 ApplySpotLight(SPOT_LIGHT light)
{
  vec4 Colour = vec4(0, 0, 0, 1);
  vec3 L = (viewMatrix * vec4(light.Position, 1)).xyz; // Calculate light position in view space
  L -= GeomResult.Position.xyz; // Find the direction from vertex to light
  L = normalize(L); // Direction should be normalized

  float NdotL = max(dot(GeomResult.Normal, L), 0);
  Colour += vec4(diffuseMaterial * light.Diffuse, 1) * NdotL;


  vec3 V = normalize(-GeomResult.Position.xyz); // Calculate direction of camera from vertex
  vec3 R = reflect(-L, GeomResult.Normal);

  float RdotV = max(dot(R, V), 0);

  if(RdotV != 0 && NdotL != 0)
    Colour += vec4(specularMaterial * light.Specular * pow(RdotV, shininessMaterial), 1);

  // Spot Factor calculation below
  vec3 D = normalize(mat3(viewMatrix) * light.Direction);
  float s = dot(-L, D);
  float alpha = acos(s);
  float deg = clamp(radians(light.Cutoff), 0, 90); // Convert cutoff to degrees and clamp between 0-90

  float spotFactor = 0;
  if(alpha <= deg) {
    spotFactor = pow(s, alpha);
  }

  // Attenuation factor below
  float dist = length(viewMatrix * vec4(light.Position, 1) - GeomResult.Position);
  float att = 1 / (QUADRATIC_ATTENTUATION * dist * dist);

  return Colour * spotFactor * att;
}
