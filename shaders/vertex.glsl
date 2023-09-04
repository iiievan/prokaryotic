#version 430 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_Texcoord;
layout (location = 2) in vec3 a_Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 fragment_Position; // for diffuse lightning
out vec2 Texcoord;

void main()
{
    gl_Position = projection * view * model * vec4(a_Pos, 1.0);
    fragment_Position = vec3(model * vec4(a_Pos, 1.0));

    // Normal = a_Normal;
    Normal = mat3(transpose(inverse(model))) * a_Normal; 
	Texcoord =  a_Texcoord;  
}