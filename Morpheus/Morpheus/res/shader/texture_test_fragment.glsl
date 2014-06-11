#version 400

uniform sampler2D texture_diffuse;

in vec4 pass_Color;
in vec2 pass_UV;

out vec4 out_Color;

void main(void)
{
   vec4 tex = texture2D(texture_diffuse, pass_UV);
   out_Color = tex;
}