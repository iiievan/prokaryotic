#version 330 core

in vec3 Normal;
in vec3 fragment_Position;  // for diffuse lightning

uniform vec3 object_Color;
uniform vec3 light_Color;
uniform vec3 light_Position;    // for diffuse lightning
uniform vec3 view_Position;     // for Specular lightning

out vec4 frag_Color;

void main()
{
    // 
    float  ambient_Strength  = 0.1;
     vec3  ambient           = ambient_Strength * light_Color;

    // 
     vec3  norm      = normalize(Normal);
     vec3  light_Dir = normalize(light_Position - fragment_Position);
    float  diff      = max(dot(norm, light_Dir), 0.0); // max 
     vec3  diffuse   = diff * light_Color;

    // 
   float  specular_Strength  = 0.5;
    vec3  view_Dir           = normalize(view_Position - fragment_Position);
    vec3  reflect_Dir        = reflect(-light_Dir, norm);
   float  spec               = pow(max(dot(view_Dir, reflect_Dir), 0.0), 64);
    vec3  specular           = specular_Strength * spec * light_Color;

    vec3  result             = (ambient + diffuse + specular) * object_Color;
      frag_Color             = vec4(result, 1.0);
}