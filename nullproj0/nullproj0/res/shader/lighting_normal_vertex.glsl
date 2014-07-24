#version 400

layout(location=0) in vec4 in_Position;
layout(location=1) in vec4 in_Normal;
layout(location=2) in vec4 in_UV;
out vec4 pass_Color;
out vec4 pass_Normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(void)
{
   gl_Position = projectionMatrix * viewMatrix * modelMatrix * in_Position;
   pass_Normal = modelMatrix * in_Normal;
   pass_Color = vec4(1, 1, 1, 1);
}