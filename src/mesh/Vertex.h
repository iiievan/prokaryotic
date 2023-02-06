#ifndef _VERTEX_H
#define _VERTEX_H

#include "glad/glad.h"
#include "glm\glm.hpp"

struct Simple_vertex			
{
	glm::vec3 position;

	Simple_vertex(glm::vec3 pos) { position = pos; }
	Simple_vertex(float x, float y, float z) { position = glm::vec3(x, y, z); }
};

struct Vertex
{
	glm::vec3  position;
	glm::vec3  color;
	glm::vec2  texture;
	//glm::vec3  normal;
	Vertex(glm::vec3 pos, glm::vec2 tex, glm::vec3 col) 
	{ position = pos; color = col;  }
	Vertex(float x, float y, float z, float t_X, float t_Y, float r, float g, float b)
	{ 
		position = glm::vec3(x, y, z);
		 texture = glm::vec2(t_X, t_Y);
		   color = glm::vec3(r, g, b); }
};

struct Coloured_vertex
{
	glm::vec4  position;
	glm::vec2  tex_coords;
	glm::vec3  normal;
	glm::vec4  color;
	  GLubyte  padding[12];	//pad to 64 bytes -> improved performance on some cards
};

struct Linked_vertex			
{
	glm::vec4 position;		//xyzw, where w contains the vertex index, 0, 1, or 2
	glm::vec2 tex_coords;
	glm::vec3 normal;
	glm::vec4 color;
	glm::vec3 p1_3d;		//The first of the other two verticies in the triangle
	glm::vec3 p2_3d;		//The second of the other two vertices in the triangle
};

// This API set input for vertex shader "layout (location = 0) in vec3 aPos;"
inline void set_Simple_vertex_attribs()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Simple_vertex), (const GLvoid*)0);
	glEnableVertexAttribArray(0);
}

inline void set_Vertex_attribs()
{
	//position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	//color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	//texcoords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(3*3*sizeof(float)));
	glEnableVertexAttribArray(2);

/*
	//normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);
	glEnableVertexAttribArray(2);
*/
}

inline void set_Coloured_vertex_attribs()
{
	//position
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Coloured_vertex), (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	//texcoords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Coloured_vertex), (const GLvoid*)16);
	glEnableVertexAttribArray(1);

	//normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Coloured_vertex), (const GLvoid*)24);
	glEnableVertexAttribArray(2);

	//color
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Coloured_vertex), (const GLvoid*)36);
	glEnableVertexAttribArray(3);
}

inline void set_Linked_vertex_attribs()
{
	//Position
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Linked_vertex), (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	//texcoords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Linked_vertex), (const GLvoid*)16);
	glEnableVertexAttribArray(1);

	//normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Linked_vertex), (const GLvoid*)24);
	glEnableVertexAttribArray(2);

	//colour
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Linked_vertex), (const GLvoid*)36);
	glEnableVertexAttribArray(3);

	//Pointers to the other vertex locations in the polygon
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Linked_vertex), (const GLvoid*)52);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Linked_vertex), (const GLvoid*)64);
	glEnableVertexAttribArray(5);
}


#endif	//_VERTEX_H
