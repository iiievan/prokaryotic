#pragma once

#include "Application.h"
#include "model/Vertex.h"
#include "shader/Shader_program.h"

namespace PROKARYOTIC
{
	extern std::vector<Simple_vertex> light_cube_vertices;

	class Light_source
	{
	public:

		Light_source(std::vector<Simple_vertex>* p_vertices)
        {
			glGenBuffers(1, &m_VBO);
            glGenVertexArrays(1, &m_VAO);

            glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Simple_vertex), (const GLvoid*)0);

			glBufferData(GL_ARRAY_BUFFER, sizeof(Simple_vertex) * p_vertices->size(), p_vertices->data(), GL_STATIC_DRAW);
        }

        unsigned int  get_VAO() const { return m_VAO; }
		unsigned int  get_VBO() const { return m_VBO; }

	private:
        unsigned int  m_VAO;
		unsigned int  m_VBO;
	};
}