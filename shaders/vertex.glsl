#version 330 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec3 a_Color;

uniform float u_Offset;

//out vec3 our_Color;
out vec3 our_Position;

void main()
{
    gl_Position = vec4(a_Pos.x,-a_Pos.y, a_Pos.z, 1.0);
    our_Position = a_Pos;
}