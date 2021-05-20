#version 330 core
out vec4 FragColor;

struct Material 
{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
        float shininess;
}; 

struct Light {
    vec3 position;    // directional light have not position
    //vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords; 

uniform vec3 viewPos;
uniform Light light;
uniform Material material;

void main()
{
    // diffuse component calculation
     vec3 norm     = normalize(Normal);
     vec3 lightDir = normalize(light.position - FragPos);
    float diff     = max(dot(norm, lightDir), 0.0);     // If the angle between both vectors is greater than 90 degrees 
                                                        // then the result of the dot product will actually become negative 
                                                        // and we end up with a negative diffuse component. For that reason we use the max function.
    // specular component calculation
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // ambient component calculation
    vec3 ambient  = light.ambient * vec3(texture(material.diffuse, TexCoords));;
    vec3 diffuse  = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));  

    vec3 emission =  texture(material.emission, TexCoords).rgb; 
    
        FragColor = vec4(ambient + diffuse + specular + emission, 1.0f);
}