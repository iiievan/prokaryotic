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
	glm::vec2  tex_coords;
	glm::vec3  normal;
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

	//texcoords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
	glEnableVertexAttribArray(1);

	//normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);
	glEnableVertexAttribArray(2);
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