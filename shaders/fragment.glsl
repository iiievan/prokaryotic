#version 430 core

in vec3 Normal;
in vec3 fragment_pos;  // for diffuse lightning
in vec2 Texcoord;

uniform vec3 object_color;
uniform vec3 view_pos;     
uniform sampler2D s_Texture_1;

out vec4 frag_color;

struct Material {
     vec3  ambient;
     vec3  diffuse;
     vec3  specular;
    float  shininess;
}; 
struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
}; 
  
uniform Material material;
uniform Light light;

void main()
{
    // ambient component
    vec3  ambient = light.ambient * material.ambient;

    // diffuse component
     vec3  norm      = normalize(Normal);
     vec3  light_dir = normalize(light.position - fragment_pos);
    float  diff      = max(dot(norm, light_dir), 0.0); // max 
     vec3  diffuse   = light.diffuse * (diff * material.diffuse);

    // specular component
    vec3  view_dir           = normalize(view_pos - fragment_pos);
    vec3  reflect_dir        = reflect(-light_dir, norm);
   float  spec               = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    vec3  specular           = light.specular * (spec * material.specular);

	  vec3  result             = (ambient + diffuse + specular);
      //frag_color               = texture(s_Texture_1, Texcoord)* vec4(result, 1.0);
	  frag_color               = vec4(result, 1.0);
}