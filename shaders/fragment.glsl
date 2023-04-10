
#version 330 core
    out vec4 frag_Color;
  
uniform vec3 object_Color;
uniform vec3 light_Color;

void main()
{
    frag_Color = vec4(light_Color * object_Color, 1.0);
}