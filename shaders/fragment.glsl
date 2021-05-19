#version 330                                                            
                                                                        
in vec4 vCol; 
in vec2 TexCoord;   // texture coordinate interpolated by vertex shader 
//flat in vec3 Normal;  // not a Phong shading;
in vec3 Normal; 
in vec3 FragPos;                                                     
                                                                        
out vec4 colour;

const int MAX_POINT_LIGHTS = 3;
const int MAX_SPOT_LIGHTS  = 3;

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

struct SpotLight
{
    PointLight  base;
          vec3  direction;
         float  edge;
};

struct Material
{
    float   specularIntensity;
    float   shininess;
};

uniform              int pointLightCount;
uniform              int spotLightCount;

uniform DirectionalLight dirLight;
uniform       PointLight pntLights[MAX_POINT_LIGHTS];
uniform        SpotLight sptLights[MAX_SPOT_LIGHTS];

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

vec4 CalcPointLight(PointLight pLight)
{
    vec3 direction = FragPos - pLight.position;

    float distance = length(direction);
         direction = normalize(direction);

    vec4 colour = calcLightByDirection(pLight.base, direction); 

    float attenuation = pLight.exponent * distance * distance +
                        pLight.linear * distance + pLight.constant;

    return (colour / attenuation);
}

vec4 CalcSpotLight(SpotLight sLight)
{
    vec3 rayDirection = normalize(FragPos - sLight.base.position);
    float slFactor = dot(rayDirection, sLight.direction);

    if (slFactor > sLight.edge)
    {
        vec4 colour = CalcPointLight(sLight.base);

        return colour*(1.0f - (1.0f - slFactor)*(1.0f/(1.0f - sLight.edge)));
    }
    else
    {
        return vec4(0, 0, 0, 0);
    }
}

vec4 CalcPointLights()
{
    vec4 totalColour = vec4(0,0,0,0);

    for (int i = 0; i < pointLightCount; i++)
    {
        totalColour += CalcPointLight(pntLights[i]);
    }

    return totalColour;
}     

vec4 CalcSpotLights()
{
    vec4 totalColour = vec4(0,0,0,0);

    for (int i = 0; i < spotLightCount; i++)
    {
        totalColour += CalcSpotLight(sptLights[i]);
    }

    return totalColour;
}                                        
                                                                        
void main()                                                             
{   
    vec4 finalColour  = CalcDirectionalLight();

         finalColour += CalcPointLights();
         finalColour += CalcSpotLights();

    colour = texture(theTexture, TexCoord) * finalColour;                                                    
}
