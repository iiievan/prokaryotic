#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
   float shininess;
};  

struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;
uniform Material material;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;   // for specular light  

void main()
{
    // diffuse component calculation
     vec3 norm = normalize(Normal);
     vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0); // If the angle between both vectors is greater than 90 degrees 
                                                // then the result of the dot product will actually become negative 
                                                // and we end up with a negative diffuse component. For that reason we use the max function.
    // specular component calculation
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // ambient component calculation
    vec3 ambient  = light.ambient * material.ambient;
    vec3 diffuse  = light.diffuse * (diff * material.diffuse);
    vec3 specular = light.specular * (spec * material.specular);  
    
    vec3 result = ambient + diffuse + specular;
      FragColor = vec4(result, 1.0);
}