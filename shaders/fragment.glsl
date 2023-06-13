#version 330 core

in vec3 Normal;
in vec3 fragment_Position;

uniform vec3 object_Color;
uniform vec3 light_Color;
uniform vec3 light_Position;

out vec4 frag_Color;

void main()
{
    // получение диффузной составлющей света
     vec3 norm = normalize(Normal);
     vec3 light_dir = normalize(light_Position - fragment_Position);
    float diff = max(dot(norm, light_dir), 0.0); // max - потому что могут быть отрицательные числа если угол больше 90
     vec3 diffuse = diff * light_Color;

     // получение составляющей рассеянного света
    float ambient_Strength = 0.1;
     vec3 ambient = ambient_Strength * light_Color;

     vec3 result = (ambient + diffuse) * object_Color;
      frag_Color = vec4(result, 1.0);
}