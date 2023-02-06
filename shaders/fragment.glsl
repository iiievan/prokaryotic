#version 330 core

in vec3  our_Color;
in vec2  our_Texture;

uniform sampler2D  s_Texture;

out vec4  frag_Color;

void main()
{
    //frag_Color = texture(s_Texture, our_Texture) * vec4(our_Color, 1.0);
    frag_Color = texture(s_Texture, our_Texture);
} 