#version 330 core

uniform vec4  Color_from_PCU;
    out vec4  Frag_color;

void main()
{
    Frag_color = Color_from_PCU;
} 