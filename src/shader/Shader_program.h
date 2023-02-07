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

        int  get_Uniform_location(const char* name) const ;
       void  set_Uniform(GLint location, float x, float y) const;
       void  set_Uniform(GLint location, float x, float y, float z) const;
       void  set_Uniform(GLint location, const glm::vec2& v) const;
       void  set_Uniform(GLint location, const glm::vec3& v) const;
       void  set_Uniform(GLint location, const glm::vec4& v) const;
       void  set_Uniform(GLint location, const glm::mat4& m) const;
       void  set_Uniform(GLint location, const glm::mat3& m) const;
       void  set_Uniform(GLint location, float val) const;
       void  set_Uniform(GLint location, int val) const;
       void  set_Uniform(GLint location, bool val) const;

       void  set_Uniform(const std::string& name, float x, float y) const;
       void  set_Uniform(const std::string& name, float x, float y, float z) const;
       void  set_Uniform(const std::string& name, const glm::vec2& v) const;
       void  set_Uniform(const std::string& name, const glm::vec3& v) const;
       void  set_Uniform(const std::string& name, const glm::vec4& v) const;
       void  set_Uniform(const std::string& name, const glm::mat4& m) const;
       void  set_Uniform(const std::string& name, const glm::mat3& m) const;
       void  set_Uniform(const std::string& name, float val) const;
       void  set_Uniform(const std::string& name, int val) const;
       void  set_Uniform(const std::string& name, bool val) const;

       void  print_Active_uniforms();
       void  print_Active_attribs();

private:
	        unsigned int  m_ID;
	std::vector<Shader*>  m_Shaders_collection;
};

#endif
