#version 330                                                            
                                                                        
in vec4 vCol; 
in vec2 TexCoord;   // texture coordinate interpolated by vertex shader 
//flat in vec3 Normal;  // not a Phong shading;
in vec3 Normal; 
in vec3 FragPos;                                                     
                                                                        
out vec4 colour;

struct DirectionalLight
{
     vec3   colour;
    float   ambientIntensity;
     vec3   direction;
    float   diffuseIntensity;
};

struct Material
{
    float   specularIntensity;
    float   shininess;
};

uniform sampler2D theTexture;   // GL_TEXTURE0 
uniform DirectionalLight dirLight;  
uniform Material material;   

uniform vec3 eyePosition;                                               
                                                                        
void main()                                                             
{          
    vec4    ambientColour = vec4(dirLight.colour, 1.0f) * dirLight.ambientIntensity;  

    // т.к. два вектора нормализованы, то diffuseFactor по сути это косинус угла между ними.
    // A.B = |A||B|cos(angle) -> A.B = 1.1.cos(angle)
    // если косинус меньше нуля, то поверхность не освещена и поэтому мы берем большее из значений
    // чтобы откинуть случаи когда мы посути не видим поверхность: cos() = 0.0f
    float   diffuseFactor = max(dot(normalize(Normal), normalize(dirLight.direction)),0.0f);
     vec4   diffuseColour = vec4(dirLight.colour, 1.0f) * dirLight.diffuseIntensity * diffuseFactor;

     vec4   specularColour = vec4(0, 0, 0, 0);

    if (diffuseFactor > 0.0f)
    {
       vec3 fragToEye = normalize(eyePosition - FragPos);
       vec3 reflectedVertex = reflect(dirLight.direction, normalize(Normal));

       float specularFactor = dot(fragToEye, reflectedVertex);

       if (specularFactor > 0.0f)
       {
           specularFactor = pow(specularFactor, material.shininess);
           specularColour = vec4(dirLight.colour * material.specularIntensity * specularFactor, 1.0f);
       }
    }

    colour = texture(theTexture, TexCoord) * (ambientColour + diffuseColour + specularColour);                                                      
}
