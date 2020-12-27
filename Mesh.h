#include <GL/glew.h>

#pragma once

class Mesh
{
public:
			Mesh() {}
		   ~Mesh() {}

	void	CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void	RenderMesh();	

private:
	GLuint VAO	{ 0 };
	GLuint VBO	{ 0 };
	GLuint IBO	{ 0 };
	GLuint indexCount	{ 0 };
};
