#version 330                                                            
                                                                        
in vec4 vCol; 
in vec2 TexCoord;   // texture coordinate interpolated by vertex shader                                                         
                                                                        
out vec4 colour;

uniform sampler2D theTexture;   // GL_TEXTURE0                                                     
                                                                        
void main()                                                             
{                                                                       
    colour = texture(theTexture, TexCoord);                                                      
}
