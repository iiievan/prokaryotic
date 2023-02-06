#version 330 core

in vec3  our_Color;
out vec4  frag_Color;

void main()
{
    frag_Color = vec4(our_Color, 1.0);
} 