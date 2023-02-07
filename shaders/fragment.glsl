#version 330 core

in vec3  our_Color;
in vec2  our_Texture_coord;

uniform sampler2D  s_Texture_1;
uniform sampler2D  s_Texture_2;

out vec4  frag_Color;

void main()
{
    //frag_Color = texture(s_Texture, our_Texture_coord) * vec4(our_Color, 1.0);
    frag_Color = mix(texture(s_Texture_1, our_Texture_coord),texture(s_Texture_2, vec2(1.0 - our_Texture_coord.x,our_Texture_coord.y)), 0.2);
} 