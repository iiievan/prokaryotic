#version 430 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_Texcoord;
layout (location = 2) in vec3 a_Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 light_pos;
uniform vec3 view_pos;
uniform vec3 light_color;

out vec3 lighting_color; // resulting color from lighting calculations

out vec2 Texcoord;

void main()
{
    gl_Position = projection * view * model * vec4(a_Pos, 1.0);


    // gouraud shading
    // ------------------------
    vec3 position = vec3(model * vec4(a_Pos, 1.0));
    vec3 normal = mat3(transpose(inverse(model))) * a_Normal;
    
    // ambient
    float ambient_strength = 0.1;
    vec3 ambient = ambient_strength * light_color;
  	
    // diffuse 
    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(light_pos - position);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = diff * light_color;
    
    // specular
    float specular_strength = 1.0; // this is set higher to better show the effect of Gouraud shading 
    vec3 view_dir = normalize(view_pos - position);
    vec3 reflect_dir = reflect(-light_dir, norm);  
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
    vec3 specular = specular_strength * spec * light_color;      

    lighting_color = ambient + diffuse + specular;	
	Texcoord =  a_Texcoord;
}