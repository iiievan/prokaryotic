#version 330 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_Tex;
layout (location = 2) in vec3 a_Color;

out vec2 our_Texture_coord;
out vec3 our_Color;

void main()
{
    gl_Position = vec4(a_Pos, 1.0);
    our_Color = a_Color;
    our_Texture_coord = a_Tex;
}