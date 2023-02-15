#ifndef __MATERIAL_H_
#define __MATERIAL_H_

#include "shader/Shader_program.h"
#include "model/Texture.h"
#include "model/Uniform_types.h"

#include <glm/glm.hpp>
#include <map>
#include <string>

#include "GLAD/glad.h"

class Shader_program;

enum e_Material_type : uint32_t
{
    MATERIAL_DEFAULT,
    MATERIAL_CUSTOM,
    MATERIAL_POST_PROCESS,
};

class Material
{
   e_Material_type  Type = MATERIAL_CUSTOM;
         glm::vec4  Color  = glm::vec4(1.0f);

              bool  Depth_test     { true };
              bool  Dept_write     { true };
            GLenum  Depth_compare  { GL_LESS };

              bool  Cull               { true };
            GLenum  Cull_face          { GL_BACK };
            GLenum  Cull_winding_order { GL_CCW };

              bool  Blend          { false };
            GLenum  Blend_src      { GL_ONE }; // pre-multiplied alpha
            GLenum  Blend_dst      { GL_ONE_MINUS_SRC_ALPHA };
            GLenum  Blend_equation { GL_FUNC_ADD };

              bool  Shadow_cast    { true };
              bool  Shadow_receive { true };

public:
                Material(Shader_program* sh_prg) 
                : m_Shader_program(sh_prg) 
                { }

Shader_program* get_Shader_program()                 const { return m_Shader_program; }
          void  set_Shader_program(Shader_program* sh_prg) { m_Shader_program = sh_prg; }

      Material  copy();

          void  set_Bool(std::string name, bool value);
          void  set_Int(std::string name, int value);
          void  set_Float(std::string name, float value);
          void  set_Vector(std::string name, glm::vec2 value);
          void  set_Vector(std::string name, glm::vec3 value);
          void  set_Vector(std::string name, glm::vec4 value);
          void  set_Matrix(std::string name, glm::mat2 value);
          void  set_Matrix(std::string name, glm::mat3 value);
          void  set_Matrix(std::string name, glm::mat4 value);

          void  set_Texture(std::string name, Texture* value, unsigned int unit = 0);
        //void  set_Texture_cube(std::string name, TextureCube* value, unsigned int unit = 0);

        std::map<std::string, Uniform_value>* get_Uniforms()         { return &m_Uniforms; }
std::map<std::string, Uniform_value_sampler>* get_Sampler_uniforms() { return &m_Sampler_uniforms; }
private:
                              Shader_program* m_Shader_program;
        std::map<std::string, Uniform_value>  m_Uniforms;
std::map<std::string, Uniform_value_sampler>  m_Sampler_uniforms; 
};
#endif //__MATERIAL_H_