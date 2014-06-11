#version 400

layout(location=0) in vec4 in_Position;
layout(location=1) in vec4 in_Normal;
layout(location=1) in vec4 in_UV;
out vec4 pass_Color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(void)
{
   gl_Position = projectionMatrix * viewMatrix * modelMatrix * in_Position;
   vec4 normal = in_Normal;
   normal /= 2;
   normal += vec4(0.5);
   normal.w = 1;
   pass_Color = normal;
}