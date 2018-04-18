#version 460

struct VERTEX_OUT
{
  vec4 Colour;
  vec4 Position;
  vec3 Normal;
  vec2 TextureCoordinate;
  vec3 TextureCoordinateCubeMap;
  vec4 ShadowCoordinate;
};

uniform float explosionElapsed;

in VERTEX_OUT vertexOut[];
out VERTEX_OUT GeomResult;


layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

void main()
{
	float speed = 2.0;
	vec3 p0 = vertexOut[1].Normal - vertexOut[0].Normal;
	vec3 p1 = vertexOut[2].Normal - vertexOut[0].Normal;
  vec3 direction = normalize(cross(p0, p1));

  if(vertexOut[0].Normal == vertexOut[1].Normal && vertexOut[1].Normal == vertexOut[2].Normal)
  {
     direction = normalize(vertexOut[1].Normal);
  }

	for(int i = 0; i < gl_in.length(); i++)
	{
		GeomResult.Colour = vertexOut[i].Colour;
		GeomResult.Position = vertexOut[i].Position;
		GeomResult.Normal = vertexOut[i].Normal;
		GeomResult.TextureCoordinate = vertexOut[i].TextureCoordinate;
		GeomResult.TextureCoordinateCubeMap = vertexOut[i].TextureCoordinateCubeMap;
		GeomResult.ShadowCoordinate = vertexOut[i].ShadowCoordinate;

		gl_Position = gl_in[i].gl_Position + vec4(direction * explosionElapsed * speed, 0.0);
		EmitVertex();
	}

	EndPrimitive();
}
