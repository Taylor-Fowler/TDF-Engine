#version 460

////////////////////////////////////
////	VERTEX ATTRIBS
////////////////////////////////////
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 vel;



////////////////////////////////////
////	UNIFORMS
////////////////////////////////////
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

uniform vec3 follow;
uniform float worldTime;

out vec4 Colour;
out vec3 pos1;
out vec3 vel1;

float rand(vec2 co);

void main(void)
{
    pos1 = pos;
    vel1 = vel;
    vel1 = normalize(vel1 + (normalize(follow - pos) * 1.2)) * 0.05;

    if(distance(pos1 + vel1, follow) < 0.02)
    {
        vec3 vel2 = vec3(
            rand(vec2(gl_VertexID, pos.z * worldTime)),
            rand(vec2(pos.x * worldTime, -gl_VertexID)),
            rand(vec2(worldTime, pos.y * -gl_VertexID / worldTime))
        ) * 2 - vec3(1, 1, 1);

        vel1 = cross(vel1, normalize(vel2)) * 0.2;//normalize(vel1 + normalize(vel2) * 0.1); // vel2 has 4x the pull
    }

    pos1 += vel1;

    //normalize(follow - pos) * 2.0 +
    Colour = vec4(abs(normalize(vel)), 1);

    gl_Position = projectionMatrix * viewMatrix * vec4(pos, 1);
}

highp float rand(vec2 co)
{
    highp float a = 12.9898;
    highp float b = 78.233;
    highp float c = 43758.5453;
    highp float dt= dot(co.xy ,vec2(a,b));
    highp float sn= mod(dt,3.14);
    return fract(sin(sn) * c);
}
