#ifndef __MESH_H
#define __MESH_H

#include "main.h"
#include "mesh/Vertex.h"

extern std::vector<Simple_vertex> triangle_vertices;
extern std::vector<Simple_vertex> rectangle_vertices;
extern std::vector<unsigned int> rectangle_indices;
extern std::vector<unsigned int> triangle_indices;

class Mesh
{
public:
	               Mesh(std::vector<Simple_vertex> vertices, std::vector<unsigned int> indices);
                   Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	              ~Mesh();

	        void  draw();

    unsigned int  get_VBO_ID() const { return m_VBO_ID; }
    unsigned int  get_VAO_ID() const { return m_VAO_ID; }
    unsigned int  get_EBO_ID() const { return m_EBO_ID; }

private:
    unsigned int  m_VBO_ID;
    unsigned int  m_VAO_ID;
    unsigned int  m_EBO_ID;

    unsigned int  m_Index_count;
};

#endif	//__MESH_H
