#version 330                                                            
                                                                        
in vec4 vCol; 
in vec2 TexCoord;   // texture coordinate interpolated by vertex shader 
//flat in vec3 Normal;  // not a Phong shading;
in vec3 Normal; 
in vec3 FragPos;                                                     
                                                                        
out vec4 colour;

const int MAX_POINT_LIGHTS = 3;

struct Light
{
     vec3   colour;
    float   ambientIntensity;
    float   diffuseIntensity;
};

struct DirectionalLight
{
    Light   base;
     vec3   direction;
};

struct PointLight
{
    Light   base;
     vec3   position;
    float   constant;
    float   linear;
    float   exponent; 
};

struct Material
{
    float   specularIntensity;
    float   shininess;
};

uniform              int pointLightCount;
uniform DirectionalLight dirLight;
uniform       PointLight pntLights[MAX_POINT_LIGHTS];

uniform        sampler2D theTexture;   // GL_TEXTURE0 
uniform         Material material;   

uniform vec3 eyePosition;

vec4    calcLightByDirection(Light light, vec3 direction)
{
    vec4    ambientColour = vec4(light.colour, 1.0f) * light.ambientIntensity;  

    // т.к. два вектора нормализованы, то diffuseFactor по сути это косинус угла между ними.
    // A.B = |A||B|cos(angle) -> A.B = 1.1.cos(angle)
    // если косинус меньше нуля, то поверхность не освещена и поэтому мы берем большее из значений
    // чтобы откинуть случаи когда мы посути не видим поверхность: cos() = 0.0f
    float   diffuseFactor = max(dot(normalize(Normal), normalize(direction)),0.0f);
     vec4   diffuseColour = vec4(light.colour  * light.diffuseIntensity * diffuseFactor, 1.0f);

     vec4   specularColour = vec4(0, 0, 0, 0);

    if (diffuseFactor > 0.0f)
    {
       vec3 fragToEye = normalize(eyePosition - FragPos);
       vec3 reflectedVertex = reflect(direction, normalize(Normal));

       float specularFactor = dot(fragToEye, reflectedVertex);

       if (specularFactor > 0.0f)
       {
           specularFactor = pow(specularFactor, material.shininess);
           specularColour = vec4(light.colour * material.specularIntensity * specularFactor, 1.0f);
       }
    }

    return (ambientColour + diffuseColour + specularColour);   
}  

vec4 CalcDirectionalLight()
{
    return calcLightByDirection(dirLight.base, dirLight.direction);
}

vec4 CalcPointLights()
{
    vec4 totalColour = vec4(0,0,0,0);

    for (int i = 0; i < pointLightCount; i++)
    {
        vec3 direction = FragPos - pntLights[i].position;

        float distance = length(direction);
        direction = normalize(direction);

        vec4 colour = calcLightByDirection(pntLights[i].base, direction); 

        float attenuation = pntLights[i].exponent * distance * distance +
                            pntLights[i].linear * distance + pntLights[i].constant;

        totalColour += (colour / attenuation);
    }

    return totalColour;
}                                             
                                                                        
void main()                                                             
{   
    vec4 finalColour  = CalcDirectionalLight();
         finalColour += CalcPointLights();
    colour = texture(theTexture, TexCoord) * finalColour;                                                    
}
