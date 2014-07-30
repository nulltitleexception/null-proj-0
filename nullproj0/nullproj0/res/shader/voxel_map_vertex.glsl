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
   pass_Color.x = ((in_Position.y * 0.9) + 0.5);
   pass_Color.y = ((in_Position.y * 0.9) + 0.5);
   pass_Color.z = ((in_Position.y * 0.9) + 0.5);
   pass_Color.w = 1.0;
}