#include "model/Material.h"

namespace PROKARYOTIC
{

    Material  Material::copy()
    {
        Material copy(&m_Shader);

        copy.Type = Type;

        copy.Color = Color;

        copy.Depth_test = Depth_test;
        copy.Dept_write = Dept_write;
        copy.Depth_compare = Depth_compare;

        copy.Cull = Cull;
        copy.Cull_face = Cull_face;
        copy.Cull_winding_order = Cull_winding_order;

        copy.Blend = Blend;
        copy.Blend_src = Blend_src;
        copy.Blend_dst = Blend_dst;
        copy.Blend_equation = Blend_equation;

        copy.m_Uniforms = m_Uniforms;
        copy.m_Sampler_uniforms = m_Sampler_uniforms;

        return copy;
    }

    void  Material::set_Bool(std::string name, bool value)
    {
        m_Uniforms[name].Type = UNIFORM_TYPE_BOOL;
        m_Uniforms[name].Bool = value;
    }

    void  Material::set_Int(std::string name, int value)
    {
        m_Uniforms[name].Type = UNIFORM_TYPE_INT;
        m_Uniforms[name].Int = value;
    }

    void  Material::set_Float(std::string name, float value)
    {
        m_Uniforms[name].Type = UNIFORM_TYPE_FLOAT;
        m_Uniforms[name].Float = value;
    }

    void  Material::set_Vector(std::string name, glm::vec2 value)
    {
        m_Uniforms[name].Type = UNIFORM_TYPE_VEC2;
        m_Uniforms[name].Vec2 = value;
    }

    void  Material::set_Vector(std::string name, glm::vec3 value)
    {
        m_Uniforms[name].Type = UNIFORM_TYPE_VEC3;
        m_Uniforms[name].Vec3 = value;
    }

    void  Material::set_Vector(std::string name, glm::vec4 value)
    {
        m_Uniforms[name].Type = UNIFORM_TYPE_VEC4;
        m_Uniforms[name].Vec4 = value;
    }

    void  Material::set_Matrix(std::string name, glm::mat2 value)
    {
        m_Uniforms[name].Type = UNIFORM_TYPE_MAT2;
        m_Uniforms[name].Mat2 = value;
    }

    void  Material::set_Matrix(std::string name, glm::mat3 value)
    {
        m_Uniforms[name].Type = UNIFORM_TYPE_MAT3;
        m_Uniforms[name].Mat3 = value;
    }

    void  Material::set_Matrix(std::string name, glm::mat4 value)
    {
        m_Uniforms[name].Type = UNIFORM_TYPE_MAT4;
        m_Uniforms[name].Mat4 = value;
    }

    void  Material::set_Texture(std::string name, Texture* value, unsigned int unit)
    {
        m_Sampler_uniforms[name].Unit = unit;
        m_Sampler_uniforms[name].Texture = value;

        switch (value->get_Target())
        {
        case GL_TEXTURE_1D:
            m_Sampler_uniforms[name].Type = UNIFORM_TYPE_SAMPLER1D;
            break;
        case GL_TEXTURE_2D:
            m_Sampler_uniforms[name].Type = UNIFORM_TYPE_SAMPLER2D;
            break;
        case GL_TEXTURE_3D:
            m_Sampler_uniforms[name].Type = UNIFORM_TYPE_SAMPLER3D;
            break;
        case GL_TEXTURE_CUBE_MAP:
            m_Sampler_uniforms[name].Type = UNIFORM_TYPE_SAMPLERCUBE;
            break;
        }

        m_Shader.use();
        m_Shader.set_Uniform(name, (int)unit);
    }
    /*
    void  Material::set_Texture_cube(std::string name, TextureCube* value, unsigned int unit = 0)
    {
        m_Sampler_uniforms[name].Unit         = unit;
        m_Sampler_uniforms[name].Type         = UNIFORM_TYPE_SAMPLERCUBE;
        m_Sampler_uniforms[name].Texture_cube = value;

        if (m_Shader_program)
        {
            m_Shader_program->use();
            m_Shader_program->set_Uniform(name, (int)unit);
        }
    }
    */

}
