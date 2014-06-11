#version 400

in vec4 pass_Color;
in vec4 pass_Normal;

out vec4 out_Color;

void main(void)
{
   vec4 light = vec4(1,-1,0,0);
   light = normalize(light);
   float lv = dot(pass_Normal, light);
   if (lv < 0){
      lv = 0;
   }
   //lv = pow(lv, 1/2.2);
   out_Color = vec4(lv, lv, lv, 1);
}