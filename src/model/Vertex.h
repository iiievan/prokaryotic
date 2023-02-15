#ifndef _VERTEX_H
#define _VERTEX_H

#include "glad/glad.h"
#include "glm\glm.hpp"

struct Simple_vertex			
{
	glm::vec3 vertices;

	Simple_vertex(glm::vec3 pos) { vertices = pos; }
	Simple_vertex(float x, float y, float z) { vertices = glm::vec3(x, y, z); }
};

struct Vertex
{
	glm::vec3  vertices;
	glm::vec2  UVs;
	glm::vec3  normals;

	Vertex(glm::vec3 vert, glm::vec2 tex, glm::vec3 norm) 
	{ vertices = vert; UVs = tex; normals = norm; }

	Vertex(float x, float y, float z, float t_X, float t_Y, float r, float g, float b)
	{ vertices = glm::vec3(x, y, z); UVs = glm::vec2(t_X, t_Y); normals = glm::vec3(r, g, b); }
};

struct Coloured_vertex
{
	glm::vec4  vertices;
	glm::vec2  UVs;
	glm::vec3  normals;
	glm::vec4  colors;
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

inline void set_vertex_attribs()
{
	// position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)0);

	// UVs
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(3 * sizeof(float)));

	// normals
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)((3 + 2) * sizeof(float)));
}

// This API set input for vertex shader "layout (location = 0) in vec3 aPos;"
inline void set_Simple_vertex_attribs()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Simple_vertex), (const GLvoid*)0);
	glEnableVertexAttribArray(0);
}

inline void set_Coloured_vertex_attribs()
{
	//position
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Coloured_vertex), (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	//UVs
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
