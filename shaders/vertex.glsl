#version 330 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec3 a_Color;

uniform float u_Offset;

out vec3 our_Color;

void main()
{
    gl_Position = vec4(a_Pos.x + u_Offset, a_Pos.y, a_Pos.z, 1.0);
    our_Color = a_Color;
}