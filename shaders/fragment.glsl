#version 430 core

in vec3 Normal;
in vec3 fragment_Position;  // for diffuse lightning
in vec2 Texcoord;
in vec3 o_Lightpos;

uniform vec3 light_Color;
uniform sampler2D s_Texture_1;

out vec4 frag_Color;

void main()
{
    // 
    float  ambient_Strength  = 0.1;
     vec3  ambient           = ambient_Strength * light_Color;

    // 
     vec3  norm      = normalize(Normal);
     vec3  light_Dir = normalize(o_Lightpos - fragment_Position);
    float  diff      = max(dot(norm, light_Dir), 0.0); // max 
     vec3  diffuse   = diff * light_Color;

    // 
   float  specular_Strength  = 0.5;
    vec3  view_Dir           = normalize(-fragment_Position);
    vec3  reflect_Dir        = reflect(-light_Dir, norm);
   float  spec               = pow(max(dot(view_Dir, reflect_Dir), 0.0), 64);
    vec3  specular           = specular_Strength * spec * light_Color;

	  vec3  result           = (ambient + diffuse + specular);
      frag_Color             = texture(s_Texture_1, Texcoord)* vec4(result, 1.0);
}