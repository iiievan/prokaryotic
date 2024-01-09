#version 430 core

in vec3 lighting_color; 
in vec2 Texcoord;

//uniform vec3 object_Color;
uniform sampler2D s_Texture_1;

out vec4 frag_Color;

void main()
{
	  //frag_Color = vec4(lighting_color * object_Color, 1.0);
	  frag_Color = texture(s_Texture_1, Texcoord) * vec4(lighting_color, 1.0);
}