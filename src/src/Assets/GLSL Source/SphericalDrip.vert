#version 460

////////////////////////////////////
////	VERTEX ATTRIBS
////////////////////////////////////
layout (location = 0) in int hit;
layout (location = 1) in float spawned;
layout (location = 2) in vec3 pos;
layout (location = 3) in vec3 velocity;


////////////////////////////////////
////	UNIFORMS
////////////////////////////////////
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

uniform vec3 ambientMaterial[2];

uniform float worldTime;
uniform vec3 spherePosition;
uniform float sphereRadius;
uniform float sphereBottomY;

out vec4 Colour;
out int hit1;
out float spawned1;
out vec3 pos1;
out vec3 velocity1;

void Reset();
float rand(vec2 co);
mat4 rotationMatrix(vec3 axis, float angle);

void main(void)
{
  hit1 = hit;
  spawned1 = spawned;
  pos1 = pos;
  velocity1 = velocity;

  if(spawned1 < worldTime)
  {
    velocity1 += vec3(0.0, -0.0001, 0.0);
    velocity1.y = max(velocity1.y, -0.01);
    //Colour = vec4(0, 1, 0, 1);
    //Colour = ApplyAmbientLight(ambientMaterial[0]);

    // As soon as it passes the floor threshold, reset it
    if(pos1.y < sphereBottomY)
    {
       Reset();
    }
    // The particle hasnt hit the sphere yet, so calculate as normal
    else if(hit == 0)
    {
      pos1 += velocity1;

      if(distance(pos1, spherePosition) < sphereRadius)
      {
        hit1 = 1;

        vec2 vel = vec2(rand(vec2(gl_VertexID, worldTime)), rand(vec2(worldTime, gl_VertexID)));
        vel = vel * 2 - vec2(1, 1);
        vel = normalize(vel);
        velocity1.x = vel.x;
        velocity1.z = vel.y;


        pos1 = spherePosition + vec3(0, 1, 0) * sphereRadius;
      }
    }
    // Particle has hit the sphere
    else
    {
      pos1.y += velocity1.y;
      if(pos1.y > sphereBottomY)
      {
        vec2 v = vec2(velocity1.x, velocity1.z);
        vec2 d = vec2(1, 0);
        float rotation = acos(velocity1.x);

        float y = pos1.y - spherePosition.y;
        float x = sqrt(sphereRadius * sphereRadius - (y * y));
        pos1 = spherePosition + vec3(rotationMatrix(vec3(0, 1, 0), rotation * 2) * vec4(x, y, 0, 1));
      }
    }
  }
  Colour = vec4(mix(ambientMaterial[0], ambientMaterial[1], clamp((pos1.y - sphereBottomY) / (sphereRadius * 2), 0.0, 1.0)), 1.0);

  gl_Position = projectionMatrix * viewMatrix * vec4(pos, 1);
}


void Reset()
{
  hit1 = 0;
  velocity1 = vec3(0, 0, 0);
  pos1 = spherePosition + (sphereRadius * vec3(0, 1, 0));
}

//https://stackoverflow.com/questions/37908924/how-to-i-modify-one-axis-of-a-rotation-matrix
mat4 rotationMatrix(vec3 axis, float angle)
{
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;

    return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}

//https://stackoverflow.com/questions/12964279/whats-the-origin-of-this-glsl-rand-one-liner
highp float rand(vec2 co)
{
    highp float a = 12.9898;
    highp float b = 78.233;
    highp float c = 43758.5453;
    highp float dt= dot(co.xy ,vec2(a,b));
    highp float sn= mod(dt,3.14);
    return fract(sin(sn) * c);
}
