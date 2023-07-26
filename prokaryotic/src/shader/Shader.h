#ifndef __SHADER_H
#define __SHADER_H

#include "Application.h"

#include <Shlwapi.h>
#include <io.h> 
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <stdint.h>

#include<GLAD/glad.h>
#include "utils/utils.h"

namespace PROKARYOTIC
{
    enum e_GLSL_shader_type : int
    {
        SHADER_NA = -1,
        VERTEX = GL_VERTEX_SHADER,
        FRAGMENT = GL_FRAGMENT_SHADER,
        GEOMETRY = GL_GEOMETRY_SHADER
    };

    enum e_shader_type 
    {
        VF,     // vertex and fragment shader
        VFG,    // vertex, fragment and geometry shader
        COMP    // compute Shader
    };

    class Shader
    {
    public:
        Shader(const std::string& vertex_fName, const std::string& frag_fName, const std::string& geo_fName, bool debug = false);     // VFG or VF Shader           
        //Shader(const GLchar* compute_Path, bool debug);                                                      // compute Shader
        ~Shader();

        void  use() { glUseProgram(m_ID); }
        //has a memory barrier to ensure what the compute shader is writing too is not read
        //void  invoke(glm::vec3 res) { if (m_type == COMP) glDispatchCompute((GLuint)res.x, (GLuint)res.y, (GLuint)res.z); }
        //void  memory_barrier() { glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT); }
      GLuint  get_ID() const { return m_ID; }

         int  get_Uniform_location(const char* name) const;
         
        void  set_Uniform(const std::string& name, float x, float y) const;
        void  set_Uniform(const std::string& name, float x, float y, float z) const;
        void  set_Uniform(const std::string& name, const glm::vec2& v) const;
        void  set_Uniform(const std::string& name, const glm::vec3& v) const;
        void  set_Uniform(const std::string& name, const glm::vec4& v) const;
        void  set_Uniform(const std::string& name, const glm::mat2& m) const;
        void  set_Uniform(const std::string& name, const glm::mat3& m) const;
        void  set_Uniform(const std::string& name, const glm::mat4& m) const;
        void  set_Uniform(const std::string& name, float val) const;
        void  set_Uniform(const std::string& name, int val) const;
        void  set_Uniform(const std::string& name, bool val) const;

        void  print_Active_uniforms();
        void  print_Active_attribs();

    private:
             GLchar*  m_Get_shader_path(const std::string& cfg_filename);
        std::string  m_Read_file(const char* filePath);
        std::string  m_Get_shader_code(const GLchar* file_Path);


        e_GLSL_shader_type  m_Shader_type { SHADER_NA };
                    GLuint  m_ID { 0 };

             e_shader_type  m_type;
             const GLchar*  m_vCode { nullptr };
             const GLchar*  m_fCode { nullptr };
             const GLchar*  m_gCode { nullptr };
    };
}




#endif	//__SHADER_H
