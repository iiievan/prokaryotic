#include "light/Light_source.h"

namespace PROKARYOTIC
{
	std::vector<Simple_vertex> light_cube_vertices =
	{
		//  only positions                            
		Simple_vertex(glm::vec3(-0.5f, -0.5f, -0.5f)),
		Simple_vertex(glm::vec3( 0.5f, -0.5f, -0.5f)),
		Simple_vertex(glm::vec3( 0.5f,  0.5f, -0.5f)),
		Simple_vertex(glm::vec3( 0.5f,  0.5f, -0.5f)),
		Simple_vertex(glm::vec3(-0.5f,  0.5f, -0.5f)),
		Simple_vertex(glm::vec3(-0.5f, -0.5f, -0.5f)),

		Simple_vertex(glm::vec3(-0.5f, -0.5f,  0.5f)),
		Simple_vertex(glm::vec3( 0.5f, -0.5f,  0.5f)),
		Simple_vertex(glm::vec3( 0.5f,  0.5f,  0.5f)),
		Simple_vertex(glm::vec3( 0.5f,  0.5f,  0.5f)),
		Simple_vertex(glm::vec3(-0.5f,  0.5f,  0.5f)),
		Simple_vertex(glm::vec3(-0.5f, -0.5f,  0.5f)),

		Simple_vertex(glm::vec3(-0.5f,  0.5f,  0.5f)),
		Simple_vertex(glm::vec3(-0.5f,  0.5f, -0.5f)),
		Simple_vertex(glm::vec3(-0.5f, -0.5f, -0.5f)),
		Simple_vertex(glm::vec3(-0.5f, -0.5f, -0.5f)),
		Simple_vertex(glm::vec3(-0.5f, -0.5f,  0.5f)),
		Simple_vertex(glm::vec3(-0.5f,  0.5f,  0.5f)),

		Simple_vertex(glm::vec3( 0.5f,  0.5f,  0.5f)),
		Simple_vertex(glm::vec3( 0.5f,  0.5f, -0.5f)),
		Simple_vertex(glm::vec3( 0.5f, -0.5f, -0.5f)),
		Simple_vertex(glm::vec3( 0.5f, -0.5f, -0.5f)),
		Simple_vertex(glm::vec3( 0.5f, -0.5f,  0.5f)),
		Simple_vertex(glm::vec3( 0.5f,  0.5f,  0.5f)),

		Simple_vertex(glm::vec3(-0.5f, -0.5f, -0.5f)),
		Simple_vertex(glm::vec3( 0.5f, -0.5f, -0.5f)),
		Simple_vertex(glm::vec3( 0.5f, -0.5f,  0.5f)),
		Simple_vertex(glm::vec3( 0.5f, -0.5f,  0.5f)),
		Simple_vertex(glm::vec3(-0.5f, -0.5f,  0.5f)),
		Simple_vertex(glm::vec3(-0.5f, -0.5f, -0.5f)),

		Simple_vertex(glm::vec3(-0.5f,  0.5f, -0.5f)),
		Simple_vertex(glm::vec3(0.5f,  0.5f, -0.5f)),
		Simple_vertex(glm::vec3(0.5f,  0.5f,  0.5f)),
		Simple_vertex(glm::vec3(0.5f,  0.5f,  0.5f)),
		Simple_vertex(glm::vec3(-0.5f,  0.5f,  0.5f)),
		Simple_vertex(glm::vec3(-0.5f,  0.5f, -0.5f))
	};

	Light_source::Light_source(Shader_program* sh_prg)
		: m_Shader_program(*sh_prg),
		Render_object(TYPE_LIGHT_SOURCE)
	{
		Topology = T_TRIANGLES;
	}

	Light_source::Light_source(std::vector<Simple_vertex>* p_vertices, Shader_program* sh_prg)
		: m_Shader_program(*sh_prg),
		Render_object(TYPE_LIGHT_SOURCE)
	{
		Topology = T_TRIANGLES;

		set_Mesh(p_vertices);
	}

	void Light_source::set_Mesh(std::vector<Simple_vertex>* p_vertices)
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

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Simple_vertex), (const GLvoid*)0);

			glBufferData(GL_ARRAY_BUFFER, sizeof(Simple_vertex) * p_vertices->size(), p_vertices->data(), GL_STATIC_DRAW);
		}
	}

	void  Light_source::set_Bool(std::string name, bool value)
	{
		m_Uniforms[name].Type = UNIFORM_TYPE_BOOL;
		m_Uniforms[name].Bool = value;
	}

	void  Light_source::set_Int(std::string name, int value)
	{
		m_Uniforms[name].Type = UNIFORM_TYPE_INT;
		m_Uniforms[name].Int = value;
	}

	void  Light_source::set_Float(std::string name, float value)
	{
		m_Uniforms[name].Type = UNIFORM_TYPE_FLOAT;
		m_Uniforms[name].Float = value;
	}

	void  Light_source::set_Vector(std::string name, glm::vec2 value)
	{
		m_Uniforms[name].Type = UNIFORM_TYPE_VEC2;
		m_Uniforms[name].Vec2 = value;
	}

	void  Light_source::set_Vector(std::string name, glm::vec3 value)
	{
		m_Uniforms[name].Type = UNIFORM_TYPE_VEC3;
		m_Uniforms[name].Vec3 = value;
	}

	void  Light_source::set_Vector(std::string name, glm::vec4 value)
	{
		m_Uniforms[name].Type = UNIFORM_TYPE_VEC4;
		m_Uniforms[name].Vec4 = value;
	}

	void  Light_source::set_Matrix(std::string name, glm::mat2 value)
	{
		m_Uniforms[name].Type = UNIFORM_TYPE_MAT2;
		m_Uniforms[name].Mat2 = value;
	}

	void  Light_source::set_Matrix(std::string name, glm::mat3 value)
	{
		m_Uniforms[name].Type = UNIFORM_TYPE_MAT3;
		m_Uniforms[name].Mat3 = value;
	}

	void  Light_source::set_Matrix(std::string name, glm::mat4 value)
	{
		m_Uniforms[name].Type = UNIFORM_TYPE_MAT4;
		m_Uniforms[name].Mat4 = value;
	}
	void  Light_source::set_Transform(glm::mat4 transform)
	{
		m_Transform = transform;
		m_Recalc = true;
	}

	void  Light_source::set_Position(glm::vec3 position)
	{
		m_Position = position;
		m_Recalc = true;
	}

	glm::mat4  Light_source::get_m4_Position()
	{
		glm::mat4 model = glm::mat4(1.0f);

		model = glm::translate(model, m_Position);

		return model;
	}

	void  Light_source::set_Scale(glm::vec3 scale)
	{
		m_Scale = scale;
		m_Recalc = true;
	}

	void  Light_source::set_Scale(float scale)
	{
		m_Scale = glm::vec3(scale);
		m_Recalc = true;
	}

	void  Light_source::set_Rotation(float radians, glm::vec3 axis)
	{
		m_Rotation = glm::vec4(axis, radians);
		m_Recalc = true;
	}

	glm::mat4  Light_source::get_Transform()
	{
		if (m_Recalc)
			update_Transform();

		return m_Transform;
	}

	void  Light_source::update_Transform()
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
