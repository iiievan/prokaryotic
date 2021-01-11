#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec3 LightPos;  
  
uniform vec3 objectColor;
uniform vec3 lightColor;  

void main()
{
   float ambientStrength = 0.1;    
    vec3 ambient = ambientStrength * lightColor;


     vec3 norm = normalize(Normal);
     vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0); // If the angle between both vectors is greater than 90 degrees 
                                                // then the result of the dot product will actually become negative 
                                                // and we end up with a negative diffuse component. For that reason we use the max function.
    vec3 diffuse = diff * lightColor;


    float specularStrength = 0.5;
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
    vec3 specular = specularStrength * spec * lightColor;  

    
    vec3 result = (specular + diffuse + ambient) * objectColor;
      FragColor = vec4(result, 1.0);
}