#version 330                                                            
                                                                        
in vec4 vCol; 
in vec2 TexCoord;   // texture coordinate interpolated by vertex shader                                                         
                                                                        
out vec4 colour;

struct DirectionalLight
{
       vec3 colour;
      float ambientIntensity;
};

uniform sampler2D theTexture;   // GL_TEXTURE0 
uniform DirectionalLight dirLight;                                                    
                                                                        
void main()                                                             
{          
    vec4 ambientColour = vec4(dirLight.colour, 1.0f) * dirLight.ambientIntensity;                                                             
    colour = texture(theTexture, TexCoord) * ambientColour;                                                      
}
