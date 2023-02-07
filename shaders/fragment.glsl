#version 330 core

in vec3  our_Color;
in vec2  our_Texture_coord;

uniform sampler2D  s_Texture_1;
uniform sampler2D  s_Texture_2;
uniform     float  f_Alpha;
uniform      bool  b_Mirror;

out vec4  frag_Color;

void main()
{
    vec2 Tex_smileface_coord;
    
    if(b_Mirror)
        Tex_smileface_coord = vec2(1.0 - our_Texture_coord.x,our_Texture_coord.y);
    else
        Tex_smileface_coord =  our_Texture_coord;

    //frag_Color = texture(s_Texture, our_Texture_coord) * vec4(our_Color, 1.0);
    frag_Color = mix(texture(s_Texture_1, our_Texture_coord),texture(s_Texture_2, Tex_smileface_coord), f_Alpha);
} 