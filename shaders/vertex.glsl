#version 330 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_Tex;

uniform mat4 transform;

out vec2 our_Texture_coord;

void main()
{
    gl_Position = transform*vec4(a_Pos, 1.0);
    our_Texture_coord = a_Tex;
}