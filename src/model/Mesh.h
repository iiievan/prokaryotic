#ifndef __MESH_H
#define __MESH_H

#include<GLAD/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include "model/Vertex.h"
#include "shader/Shader_program.h"

extern std::vector<Simple_vertex> triangle_vertices;
extern std::vector<Simple_vertex> triangle2_vertices;
extern std::vector<Vertex> rectangle_vertices;
extern std::vector<Vertex> coloured_triangle;
extern std::vector<unsigned int> rectangle_indices;
extern std::vector<unsigned int> triangle_indices;

class Shader_program;

namespace PROKARYOTIC
{  
    enum TOPOLOGY : uint32_t
    {
        POINTS,
        LINES,
        LINE_STRIP,
        TRIANGLES,
        TRIANGLE_STRIP,
        TRIANGLE_FAN,
    };

    template <typename T> void set_vertex_attribs();

    template <typename T>
    class Mesh
    {
        TOPOLOGY  Topology{ TRIANGLES };
    public:
        Mesh();
        Mesh(std::vector<T>* p_vertices, std::vector<unsigned int>* p_indices)
        {
            if (p_indices != nullptr)
                m_Index_count = p_indices->size();

            m_Vertices = p_vertices;

            //push the mesh
            glGenBuffers(1, &m_VBO_ID);
            glGenVertexArrays(1, &m_VAO_ID);
            glGenBuffers(1, &m_EBO_ID);

            glBindVertexArray(m_VAO_ID);
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO_ID);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO_ID);

            glBufferData(GL_ARRAY_BUFFER, sizeof(T) * p_vertices->size(), &p_vertices[0], GL_STATIC_DRAW);
            set_vertex_attribs<T>();
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * p_indices->size(), &p_indices[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            //GL_STREAM_DRAW: данные устанавливаются только один раз и используются графическим процессором не более нескольких раз.
            //GL_STATIC_DRAW : данные устанавливаются только один раз и используются многократно.
            //GL_DYNAMIC_DRAW : данные сильно изменяются и используются многократно.
        }

        ~Mesh()
        {
            glDeleteVertexArrays(1, &m_VAO_ID);
            glDeleteBuffers(1, &m_VBO_ID);
            glDeleteBuffers(1, &m_EBO_ID);
        }

        template<typename SH = Shader_program>
        inline void  draw(SH* p_Sh_prg, bool vireframe_mode = false)
        {
            if (vireframe_mode)
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

            // if shader program is presented, use it.
            if (p_Sh_prg != nullptr)
                p_Sh_prg->use();

            glBindVertexArray(m_VAO_ID);
            if (m_Index_count)
            {
                glDrawElements(Topology == TRIANGLE_STRIP ? GL_TRIANGLE_STRIP : GL_TRIANGLES, m_Index_count, GL_UNSIGNED_INT, 0);
            }
            else
            {
                glDrawArrays(Topology == TRIANGLE_STRIP ? GL_TRIANGLE_STRIP : GL_TRIANGLES, 0, m_Vertices->size());
            }

            glBindVertexArray(0);
        }

        int  get_max_vertex_attributes()
        {
            int nrAttributes;
            glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);

            printf("Maximum nr of vertex attributes supported: %d", nrAttributes);

            return nrAttributes;
        }

        unsigned int  get_VBO_ID() const { return m_VBO_ID; }
        unsigned int  get_VAO_ID() const { return m_VAO_ID; }
        unsigned int  get_EBO_ID() const { return m_EBO_ID; }

    private:
        std::vector<T>* m_Vertices;
        unsigned int  m_Index_count{ 0 };

        unsigned int  m_VBO_ID;
        unsigned int  m_VAO_ID;
        unsigned int  m_EBO_ID;
    };  

    template <>
    inline void set_vertex_attribs<Vertex>()
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

    template <>
    inline void set_vertex_attribs<Simple_vertex>()
    {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Simple_vertex), (const GLvoid*)0);
    }
}

#endif	//__MESH_H
