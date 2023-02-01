#ifndef __MESH_H
#define __MESH_H

#include "main.h"

extern float mesh_vertices[];

class Mesh
{
public:
	       Mesh(float *vertices);
	      ~Mesh();

	       void  load_to_GPU(size_t vertices_num);
	       void  draw();

    unsigned int get_VBO_ID() const { return m_VBO_ID; }
    unsigned int get_VAO_ID() const { return m_VAO_ID; }
    unsigned int get_EBO_ID() const { return m_EBO_ID; }

private:
    unsigned int m_VBO_ID;
    unsigned int m_VAO_ID;
    unsigned int m_EBO_ID;

    const float *m_Vertices;
};

#endif	//__MESH_H
