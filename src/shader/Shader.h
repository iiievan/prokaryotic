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

#define access _access_s

class Shader
{
public:
    	         Shader(const std::string &GLSL_filename, GLuint type);
                 ~Shader();
    
    	    void  compile();
    unsigned int  get_shader_ID() const { return m_Shader_glID; }

private:
          GLuint  m_Shader_type;
	 std::string  m_Shader_source_code;
	unsigned int  m_Shader_glID;
	        char  m_info_log[512];
};


extern        char* get_shader_path(const std::string& cfg_filename);
extern std::string  operator-(std::string source, const std::string& target);
extern std::string  Read_file(const char* filePath);
//extern      GLuint  Load_shader(const char* vertex_path, const char* fragment_path);


#endif	//__SHADER_H
