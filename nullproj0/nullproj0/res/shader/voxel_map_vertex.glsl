#version 400

layout(location=0) in vec4 in_Position;
layout(location=1) in vec4 in_Normal;
layout(location=2) in vec2 in_UV;

out vec4 pass_Color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(void)
{
   gl_Position = projectionMatrix * viewMatrix * modelMatrix * in_Position;
   float l = (in_Position.y / 7.5) + 0.5;
   //float l = dot(in_Normal.xyz, normalize(vec3(0, 1, 1)));
   pass_Color.x = l;
   pass_Color.y = l;
   pass_Color.z = l;
   pass_Color.w = 1.0;
}