#version 330                                                            
                                                                        
in vec4 vCol; 
in vec2 TexCoord;   // texture coordinate interpolated by vertex shader 
//flat in vec3 Normal;  // not a Phong shading;
in vec3 Normal;                                                      
                                                                        
out vec4 colour;

struct DirectionalLight
{
       vec3 colour;
      float ambientIntensity;
       vec3 direction;
      float diffuseIntensity;
};

uniform sampler2D theTexture;   // GL_TEXTURE0 
uniform DirectionalLight dirLight;                                                    
                                                                        
void main()                                                             
{          
    vec4 ambientColour = vec4(dirLight.colour, 1.0f) * dirLight.ambientIntensity;  

    // т.к. два вектора нормализованы, то diffuseFactor по сути это косинус угла между ними.
    // A.B = |A||B|cos(angle) -> A.B = 1.1.cos(angle)
    // если косинус меньше нуля, то поверхность не освещена и поэтому мы берем большее из значений
    // чтобы откинуть случаи когда мы посути не видим поверхность: cos() = 0.0f
    float   diffuseFactor = max(dot(normalize(Normal), normalize(dirLight.direction)),0.0f);
     vec4   diffuseColour = vec4(dirLight.colour, 1.0f) * dirLight.diffuseIntensity * diffuseFactor;

    colour = texture(theTexture, TexCoord) * (ambientColour + diffuseColour);                                                      
}
