#ifndef _VERTEX_H
#define _VERTEX_H

#include "glad/glad.h"
#include "glm\glm.hpp"

namespace PROKARYOTIC
{
	struct Simple_vertex
	{
		glm::vec3 position;

		Simple_vertex(glm::vec3 pos) { position = pos; }
		Simple_vertex(float x, float y, float z) { position = glm::vec3(x, y, z); }
	};

	struct Vertex
	{
		glm::vec3  vertices;
		glm::vec2  UVs;
		glm::vec3  normals;

		Vertex(glm::vec3 vert, glm::vec2 tex, glm::vec3 norm)
		{
			vertices = vert; UVs = tex; normals = norm;
		}

		Vertex(float x, float y, float z, float t_X, float t_Y, float r, float g, float b)
		{
			vertices = glm::vec3(x, y, z); UVs = glm::vec2(t_X, t_Y); normals = glm::vec3(r, g, b);
		}
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
		glm::vec4 vertices;		//xyzw, where w contains the vertex index, 0, 1, or 2
		glm::vec2 UVs;
		glm::vec3 normals;
		glm::vec4 colors;
		glm::vec3 p1_3d;		//The first of the other two verticies in the triangle
		glm::vec3 p2_3d;		//The second of the other two vertices in the triangle
	};
}

#endif	//_VERTEX_H
