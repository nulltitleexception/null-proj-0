#version 400

layout(location=0) in vec4 in_Position;
layout(location=1) in vec4 in_Normal;
layout(location=2) in vec2 in_UV;

out vec4 pass_Color;
out vec2 pass_UV;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(void)
{
   gl_Position = projectionMatrix * viewMatrix * modelMatrix * in_Position;
   pass_Color.r = in_UV.x;
   pass_Color.g = in_UV.y;
   pass_UV = in_UV;
}