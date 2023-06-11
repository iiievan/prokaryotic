#version 330 core

    out vec4 frag_Color;
  
uniform vec3 object_Color;
uniform vec3 light_Color;

void main()
{
    float ambient_Strength = 0.1;
     vec3 ambient = ambient_Strength * light_Color;
     vec3  result = ambient * object_Color;

    frag_Color = vec4(result, 1.0);
}