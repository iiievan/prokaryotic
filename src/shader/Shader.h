#ifndef __SHADER_H
#define __SHADER_H

#include "main.h"

#include <Shlwapi.h>
#include <io.h> 
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <stdint.h>

#include "utils/utils.h"

enum e_GLSL_shader_type : int8_t 
{
    SHADER_NA = -1,
    VERTEX    =  0,
    FRAGMENT,
    GEOMETRY
};

class Shader
{
public:
    	         Shader(const std::string &GLSL_filename, e_GLSL_shader_type type);
                ~Shader();

    	    bool  compile(GLuint shader_program_ID);
            bool  link(GLuint shader_program_ID);
            bool  validate(GLuint shader_program_ID);
            bool  link_and_validate(GLuint shader_program_ID);
            void  use();

          GLuint  get_ID() const { return m_ID; }

            bool  linked    { false };
            bool  validated { false };

private:
            char* m_Get_shader_path(const std::string& cfg_filename);
     std::string  m_Read_file(const char* filePath);

    e_GLSL_shader_type  m_Shader_type { SHADER_NA };
	   std::string  m_Shader_source_code;
            GLuint  m_ID { 0 };
            GLuint  m_shader_program_ID { 0 };
};





#endif	//__SHADER_H
