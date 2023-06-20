#pragma once

#include "Application.h"
#include "model/Vertex.h"
#include "shader/Shader_program.h"
#include "model/Uniform_types.h"
#include "renderer/Render_object.h"
#include "model/Mesh.h"

#include <glm/glm.hpp>
#include <map>
#include <string>

namespace PROKARYOTIC
{
	extern std::vector<Vertex> rectangle_vertices;	

    enum  TOPOLOGY : uint32_t;

	class UI_item : public Render_object
	{
		TOPOLOGY  Topology;

	public:

		UI_item(Shader_program* sh_prg);
		UI_item(std::vector<Vertex>* p_vertices, Shader_program* sh_prg);

		std::uint64_t  get_ID() const { return Render_object::m_ID.raw; }

		                      Shader_program& get_Shader_program() const { return m_Shader_program; }
		std::map<std::string, Uniform_value>* get_Uniforms()             { return &m_Uniforms; }

		void  set_Mesh(std::vector<Vertex>* p_vertices);

		void  set_Bool(std::string name, bool value);
		void  set_Int(std::string name, int value);
		void  set_Float(std::string name, float value);
		void  set_Vector(std::string name, glm::vec2 value);
		void  set_Vector(std::string name, glm::vec3 value);
		void  set_Vector(std::string name, glm::vec4 value);
		void  set_Matrix(std::string name, glm::mat2 value);
		void  set_Matrix(std::string name, glm::mat3 value);
		void  set_Matrix(std::string name, glm::mat4 value);

		void  set_Position(glm::vec3 position);
   glm::mat4  get_m4_Position();
   glm::vec3  get_v3_Position() const { return m_Position; }
   glm::vec4  get_v4_Position() const { return glm::vec4(m_Position.x, m_Position.y, m_Position.z, 1.0f); }
		void  set_Scale(glm::vec3 scale);
		void  set_Scale(float scale);
		void  set_Rotation(float degrees, glm::vec3 axis);
		void  set_Transform(glm::mat4 transform);
   glm::mat4  get_Transform();
		void  update_Transform();

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

			if (m_VAO)
			{
				glBindVertexArray(m_VAO);

				glDrawArrays(Topology == T_TRIANGLE_STRIP ? GL_TRIANGLE_STRIP : GL_TRIANGLES, 0, m_Vertices->size());
				glBindVertexArray(0);
			}
			else
			{
				return;
			}
		}

        unsigned int  get_VAO() const { return m_VAO; }
		unsigned int  get_VBO() const { return m_VBO; }

	private:
		                     Shader_program&  m_Shader_program;
		std::map<std::string, Uniform_value>  m_Uniforms;
		                std::vector<Vertex>* m_Vertices {nullptr};

		      glm::mat4  m_Transform{ glm::mat4(1.0f) };
		      glm::vec3  m_Position{ glm::vec3(0.0f) };
		      glm::vec4  m_Rotation{ glm::vec4(0.0f,0.0f,1.0f,0.0f) }; // XYZ and W - radians
		      glm::vec3  m_Scale{ glm::vec3(1.0f) };
		      
		           bool  m_Recalc{ false };           // mark the current object's tranform as dirty if it needs to be re-calculated this frame

		   unsigned int  m_VAO { 0 };
		   unsigned int  m_VBO { 0 };
	};
}