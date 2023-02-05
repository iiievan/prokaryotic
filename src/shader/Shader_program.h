#ifndef __SHADER_PROGRAMM_H_
#define __SHADER_PROGRAMM_H_

#include <vector> 
#include "shader/Shader.h"

class Shader;

class Shader_program
{
public:
		      Shader_program();
		      ~Shader_program();

		void  load_shader(Shader* p_Sh);
		void  use();
unsigned int  get_ID() const { return m_ID; }

       void  bind_Attrib_location(GLuint location, const char* name);
       void  bind_Frag_data_location(GLuint location, const char* name);

        int  get_Uniform_location(const char* name);
       void  set_Uniform(GLint location, float x, float y);
       void  set_Uniform(GLint location, float x, float y, float z);
       void  set_Uniform(GLint location, const glm::vec2& v);
       void  set_Uniform(GLint location, const glm::vec3& v);
       void  set_Uniform(GLint location, const glm::vec4& v);
       void  set_Uniform(GLint location, const glm::mat4& m);
       void  set_Uniform(GLint location, const glm::mat3& m);
       void  set_Uniform(GLint location, float val);
       void  set_Uniform(GLint location, int val);
       void  set_Uniform(GLint location, bool val);
       void  print_Active_uniforms();
       void  print_Active_attribs();

private:
	        unsigned int  m_ID;
				    char  m_info_log[512];
	std::vector<Shader*>  m_Shaders_collection;
};

#endif
