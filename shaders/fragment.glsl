#version 330 core

//in vec3  our_Color;
in vec3 our_Position;
out vec4  frag_Color;

void main()
{
    frag_Color = vec4(our_Position, 1.0);
} 