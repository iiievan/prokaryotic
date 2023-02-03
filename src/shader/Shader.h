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

            void  print_log();
    	    bool  compile();
            bool  link();
            bool  validate();
            bool  link_and_validate();
            void  use();

          GLuint  get_ID() const { return m_shader_ID; }
          GLuint  get_shader_program_ID() const { return m_shader_program_ID; }
            bool  get_linked_sts() const { return m_Linked; }
            bool  get_validated_sts() const { return m_Validated; }

            void  bind_Attrib_location(GLuint location, const char* name);
            void  bind_Frag_data_location(GLuint location, const char* name);

     int get_Uniform_location(const char* name);
    void set_Uniform(GLint location, float x, float y);
    void set_Uniform(GLint location, float x, float y, float z);
    void set_Uniform(GLint location, const glm::vec2& v);
    void set_Uniform(GLint location, const glm::vec3& v);
    void set_Uniform(GLint location, const glm::vec4& v);
    void set_Uniform(GLint location, const glm::mat4& m);
    void set_Uniform(GLint location, const glm::mat3& m);
    void set_Uniform(GLint location, float val);
    void set_Uniform(GLint location, int val);
    void set_Uniform(GLint location, bool val);
    void print_Active_uniforms();
    void print_Active_attribs();

private:
    e_GLSL_shader_type  m_Shader_type { SHADER_NA };
	   std::string  m_Shader_source_code;
            GLuint  m_shader_ID { 0 };
            GLuint  m_shader_program_ID { 0 };
	   std::string  m_info_log;

              bool  m_Linked {false};
              bool  m_Validated {false};
};


extern        char* get_shader_path(const std::string& cfg_filename);
extern std::string  operator-(std::string source, const std::string& target);
extern std::string  Read_file(const char* filePath);
//extern      GLuint  Load_shader(const char* vertex_path, const char* fragment_path);


#endif	//__SHADER_H
