#include "userinterface/UI_item.h"

namespace PROKARYOTIC
{
	UI_item::UI_item(Shader_program* sh_prg)
		: m_Shader_program(*sh_prg),
		Render_object(TYPE_UI_ITEM)
	{
		Topology = T_TRIANGLES;
	}

	UI_item::UI_item(std::vector<Vertex>* p_vertices, Shader_program* sh_prg)
		: m_Shader_program(*sh_prg),
		Render_object(TYPE_UI_ITEM)
	{
		Topology = T_TRIANGLES;

		set_Mesh(p_vertices);
	}

	void UI_item::set_Mesh(std::vector<Vertex>* p_vertices)
	{
		// not generate VAO and VBO if no Mesh
		if (p_vertices != nullptr)
		{
			m_Vertices = p_vertices;

			if (!m_VBO)
				glGenBuffers(1, &m_VBO);

			if (!m_VAO)
				glGenVertexArrays(1, &m_VAO);

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        	// position
        	glEnableVertexAttribArray(0);
        	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)0);

        	// UVs
        	glEnableVertexAttribArray(1);
        	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(3 * sizeof(float)));

			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * p_vertices->size(), p_vertices->data(), GL_STATIC_DRAW);
		}
	}

	void  UI_item::set_Bool(std::string name, bool value)
	{
		m_Uniforms[name].Type = UNIFORM_TYPE_BOOL;
		m_Uniforms[name].Bool = value;
	}

	void  UI_item::set_Int(std::string name, int value)
	{
		m_Uniforms[name].Type = UNIFORM_TYPE_INT;
		m_Uniforms[name].Int = value;
	}

	void  UI_item::set_Float(std::string name, float value)
	{
		m_Uniforms[name].Type = UNIFORM_TYPE_FLOAT;
		m_Uniforms[name].Float = value;
	}

	void  UI_item::set_Vector(std::string name, glm::vec2 value)
	{
		m_Uniforms[name].Type = UNIFORM_TYPE_VEC2;
		m_Uniforms[name].Vec2 = value;
	}

	void  UI_item::set_Vector(std::string name, glm::vec3 value)
	{
		m_Uniforms[name].Type = UNIFORM_TYPE_VEC3;
		m_Uniforms[name].Vec3 = value;
	}

	void  UI_item::set_Vector(std::string name, glm::vec4 value)
	{
		m_Uniforms[name].Type = UNIFORM_TYPE_VEC4;
		m_Uniforms[name].Vec4 = value;
	}

	void  UI_item::set_Matrix(std::string name, glm::mat2 value)
	{
		m_Uniforms[name].Type = UNIFORM_TYPE_MAT2;
		m_Uniforms[name].Mat2 = value;
	}

	void  UI_item::set_Matrix(std::string name, glm::mat3 value)
	{
		m_Uniforms[name].Type = UNIFORM_TYPE_MAT3;
		m_Uniforms[name].Mat3 = value;
	}

	void  UI_item::set_Matrix(std::string name, glm::mat4 value)
	{
		m_Uniforms[name].Type = UNIFORM_TYPE_MAT4;
		m_Uniforms[name].Mat4 = value;
	}
	void  UI_item::set_Transform(glm::mat4 transform)
	{
		m_Transform = transform;
		m_Recalc = true;
	}

	void  UI_item::set_Position(glm::vec3 position)
	{
		m_Position = position;
		m_Recalc = true;
	}

	glm::mat4  UI_item::get_m4_Position()
	{
		glm::mat4 model = glm::mat4(1.0f);

		model = glm::translate(model, m_Position);

		return model;
	}

	void  UI_item::set_Scale(glm::vec3 scale)
	{
		m_Scale = scale;
		m_Recalc = true;
	}

	void  UI_item::set_Scale(float scale)
	{
		m_Scale = glm::vec3(scale);
		m_Recalc = true;
	}

	void  UI_item::set_Rotation(float radians, glm::vec3 axis)
	{
		m_Rotation = glm::vec4(axis, radians);
		m_Recalc = true;
	}

	glm::mat4  UI_item::get_Transform()
	{
		if (m_Recalc)
			update_Transform();

		return m_Transform;
	}

	void  UI_item::update_Transform()
	{
		// we only do this if the node itself or its parent is flagged as dirty
		if (m_Recalc)
		{
			// first translation , then scale, then rotate.
			m_Transform = glm::translate(m_Transform, m_Position);
			m_Transform = glm::scale(m_Transform, m_Scale);
			m_Transform = glm::rotate(m_Transform, m_Rotation.w, glm::vec3(m_Rotation));
		}

		m_Recalc = false;
	}
}
