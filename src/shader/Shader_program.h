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
		 int  link_program();
		void  use();
unsigned int  get_shader_ID() const { return m_gl_ID; }

private:
	        unsigned int  m_gl_ID;
				    char  m_info_log[512];
	std::vector<Shader*>  m_Shaders_collection;
};

#endif
