#version 430 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_Texcoord;
layout (location = 2) in vec3 a_Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 light_Position;    // for diffuse lightning

out vec3 Normal;
out vec3 fragment_Position; // for diffuse lightning
out vec2 Texcoord;
out vec3 o_Lightpos;

void main()
{
    gl_Position = projection * view * model * vec4(a_Pos, 1.0);
    fragment_Position = vec3(view * model * vec4(a_Pos, 1.0));

    // Normal = a_Normal;
    Normal = mat3(transpose(inverse(view * model))) * a_Normal; 
	Texcoord =  a_Texcoord;  
	o_Lightpos = vec3(view * vec4(light_Position, 1.0)); // Transform world-space light position to view-space light position
	
}