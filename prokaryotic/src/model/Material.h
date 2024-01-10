#ifndef __MATERIAL_H_
#define __MATERIAL_H_

#include "shader/Shader.h"
#include "model/Texture.h"
#include "model/Uniform_types.h"

#include <glm/glm.hpp>
#include <map>
#include <string>

#include "GLAD/glad.h"

namespace PROKARYOTIC
{
    enum e_Material_type : uint32_t
    {
        MATERIAL_DEFAULT,
        MATERIAL_CUSTOM,
        MATERIAL_POST_PROCESS,
    };

    enum e_simple_props
    {
        PROP_EMERALD = 0,
        PROP_JADE,
        PROP_OBSIDIAN,
        PROP_PEARL,
        PROP_RUBY,
        PROP_TURQUOISE,
        PROP_BRASS,
        PROP_BRONZE,
        PROP_CHROME,
        PROP_COPPER,
        PROP_GOLD,
        PROP_SILVER,
        PROP_BLACK_PLASTIC,
        PROP_CYAN_PLASTIC,
        PROP_GREEN_PLASTIC,
        PROP_RED_PLASTIC,
        PROP_WHITE_PLASTIC,
        PROP_YELLOW_PLASTIC,
        PROP_BLACK_RUBBER,
        PROP_CYAN_RUBBER,
        PROP_GREEN_RUBBER,
        PROP_RED_RUBBER,
        PROP_WHITE_RUBBER,
        PROP_YELLOW_RUBBER
    };

    struct material_props_t
    {
        glm::vec3  ambient;
        glm::vec3  diffuse;
        glm::vec3  specular;
            float  shininess;

        material_props_t(glm::vec3 am, glm::vec3 diff, glm::vec3 spec, float sh)
        : ambient(am),diffuse(diff),specular(spec),shininess(sh) 
        { }

        material_props_t(e_simple_props prop)
        {
            switch (prop)
            {
                case PROP_EMERALD:
                    ambient = glm::vec3(0.0215f, 0.1745f, 0.0215f); diffuse = glm::vec3(0.07568f, 0.61424f, 0.07568f); specular = glm::vec3(0.633f, 0.727811f, 0.633f); shininess = 0.6f;
                    break;
                case PROP_JADE:
                    ambient = glm::vec3(0.135f, 0.2225f, 0.1575f); diffuse = glm::vec3(0.54f, 0.89f, 0.63f); specular = glm::vec3(0.316228f, 0.316228f, 0.316228f); shininess = 0.1f;
                    break;
                case PROP_OBSIDIAN:
                    ambient = glm::vec3(0.05375f, 0.05f, 0.06625f); diffuse = glm::vec3(0.18275f, 0.17f, 0.22525f); specular = glm::vec3(0.332741f, 0.328634f, 0.346435f); shininess = 0.3f;
                    break;
                case PROP_PEARL:			
                    ambient = glm::vec3(0.25f, 0.20725f, 0.20725f); diffuse = glm::vec3(1.0f, 0.829f, 0.829f); specular = glm::vec3(0.296648f, 0.296648f, 0.296648f); shininess = 0.088f;
                    break;
                case PROP_RUBY:	
                    ambient = glm::vec3(0.1745f, 0.01175f, 0.01175f); diffuse = glm::vec3(0.61424f, 0.04136f, 0.04136f); specular = glm::vec3(0.727811f, 0.626959f, 0.626959f); shininess = 0.6f;
                    break;
                case PROP_TURQUOISE: 			
                    ambient = glm::vec3(0.1f, 0.18725f, 0.1745f); diffuse = glm::vec3(0.396f, 0.74151f, 0.69102f); specular = glm::vec3(0.297254f, 0.30829f, 0.306678f); shininess = 0.1f;
                    break;
                case PROP_BRASS: 	
                    ambient = glm::vec3(0.329412f, 0.223529f, 0.027451f); diffuse = glm::vec3(0.780392f, 0.568627f, 0.113725f); specular = glm::vec3(0.992157f,	0.941176f, 0.807843f); shininess = 0.21794872f;
                    break;
                case PROP_BRONZE: 			
                    ambient = glm::vec3(0.2125f, 0.1275f, 0.054f); diffuse = glm::vec3(0.714f, 0.4284f, 0.18144f); specular = glm::vec3(0.393548f, 0.271906f, 0.166721f); shininess = 0.2f;
                    break;
                case PROP_CHROME: 				
                    ambient = glm::vec3(0.25f, 0.25f, 0.25f); diffuse = glm::vec3(0.4f, 0.4f, 0.4f); specular = glm::vec3(0.774597f, 0.774597f, 0.774597f); shininess = 0.6f;
                    break;
                case PROP_COPPER: 		
                    ambient = glm::vec3(0.19125f, 0.0735f, 0.0225f); diffuse = glm::vec3(0.7038f, 0.27048f, 0.0828f); specular = glm::vec3(0.256777f, 0.137622f, 0.086014f); shininess = 0.1f;
                    break;
                case PROP_GOLD: 			
                    ambient = glm::vec3(0.24725f, 0.1995f, 0.0745f); diffuse = glm::vec3(0.75164f, 0.60648f, 0.22648f); specular = glm::vec3(0.628281f, 0.555802f, 0.366065f); shininess = 0.4f;
                    break;
                case PROP_SILVER: 			
                    ambient = glm::vec3(0.19225f, 0.19225f, 0.19225f); diffuse = glm::vec3(0.50754f, 0.50754f, 0.50754f); specular = glm::vec3(0.508273f, 0.508273f, 0.508273f); shininess = 0.4f;
                    break;
                case PROP_BLACK_PLASTIC: 			
                    ambient = glm::vec3(0.0f, 0.0f, 0.0f); diffuse = glm::vec3(0.01f, 0.01f, 0.01f); specular = glm::vec3(0.50f, 0.50f, 0.50f); shininess = 0.25f;
                    break;
                case PROP_CYAN_PLASTIC: 	
                    ambient = glm::vec3(0.0f, 0.1f, 0.06f); diffuse = glm::vec3(0.0f, 0.50980392f, 0.50980392f); specular = glm::vec3(0.50196078f, 0.50196078f, 0.50196078f); shininess = 0.25f;
                    break;
                case PROP_GREEN_PLASTIC: 			
                    ambient = glm::vec3(0.0f, 0.0f, 0.0f); diffuse = glm::vec3(0.1f, 0.35f, 0.1f); specular = glm::vec3(0.45f, 0.55f, 0.45f); shininess = 0.25f;
                    break;
                case PROP_RED_PLASTIC: 			
                    ambient = glm::vec3(0.0f, 0.0f, 0.0f); diffuse = glm::vec3(0.5f, 0.0f, 0.0f); specular = glm::vec3(0.7f, 0.6f, 0.6f); shininess = 0.25f;
                    break;
                case PROP_WHITE_PLASTIC: 			
                    ambient = glm::vec3(0.0f, 0.0f, 0.0f); diffuse = glm::vec3(0.55f, 0.55f, 0.55f); specular = glm::vec3(0.70f, 0.70f, 0.70f); shininess = 0.25f;
                    break;
                case PROP_YELLOW_PLASTIC: 			
                    ambient = glm::vec3(0.0f, 0.0f, 0.0f); diffuse = glm::vec3(0.5f, 0.5f, 0.0f); specular = glm::vec3(0.60f, 0.60f, 0.50f); shininess = 0.25f;
                    break;
                case PROP_BLACK_RUBBER: 			
                    ambient = glm::vec3(0.02f, 0.02f, 0.02f); diffuse = glm::vec3(0.01f, 0.01f, 0.01f); specular = glm::vec3(0.4f, 0.4f, 0.4f); shininess = 0.078125f;
                    break;
                case PROP_CYAN_RUBBER: 			
                    ambient = glm::vec3(0.0f, 0.05f, 0.05f); diffuse = glm::vec3(0.4f, 0.5f, 0.5f); specular = glm::vec3(0.04f, 0.7f, 0.7f); shininess = 0.078125f;
                    break;
                case PROP_GREEN_RUBBER: 			
                    ambient = glm::vec3(0.0f, 0.05f, 0.0f); diffuse = glm::vec3(0.4f, 0.5f, 0.4f); specular = glm::vec3(0.04f, 0.7f, 0.04f); shininess = 0.078125f;
                    break;
                case PROP_RED_RUBBER: 		
                    ambient = glm::vec3(0.05f, 0.0f, 0.0f); diffuse = glm::vec3(0.5f, 0.4f, 0.4f); specular = glm::vec3(0.7f, 0.04f, 0.04f); shininess = 0.078125f;
                    break;
                case PROP_WHITE_RUBBER: 				
                    ambient = glm::vec3(0.05f, 0.05f, 0.05f); diffuse = glm::vec3(0.5f, 0.5f, 0.5f); specular = glm::vec3(0.7f, 0.7f, 0.7f); shininess = 0.078125f;
                    break;
                case PROP_YELLOW_RUBBER: 			
                    ambient = glm::vec3(0.05f, 0.05f, 0.0f); diffuse = glm::vec3(0.5f, 0.5f, 0.4f); specular = glm::vec3(0.7f, 0.7f, 0.04f); shininess = 0.078125f;
                    break;
                default:
                    ambient = glm::vec3(); diffuse = glm::vec3(); specular = glm::vec3(); shininess = 0.f;
                    break;
            }
        }
    };

    class Shader;

    class Material
    {
        e_Material_type  Type = MATERIAL_CUSTOM;
        glm::vec4  Color = glm::vec4(1.0f);

          bool  Depth_test{ true };
          bool  Dept_write{ true };
        GLenum  Depth_compare{ GL_LESS };

          bool  Cull{ true };
        GLenum  Cull_face{ GL_BACK };
        GLenum  Cull_winding_order{ GL_CCW };

        bool  Blend{ false };
        GLenum  Blend_src{ GL_ONE }; // pre-multiplied alpha
        GLenum  Blend_dst{ GL_ONE_MINUS_SRC_ALPHA };
        GLenum  Blend_equation{ GL_FUNC_ADD };

        bool  Shadow_cast{ true };
        bool  Shadow_receive{ true };

    public:
        Material(Shader* sh_prg)
        : m_Shader(*sh_prg)
        { }

        Shader& get_Shader() const { return m_Shader; }

        Material  copy();
        
        void  set_Uniform(const std::string& name, float x, float y);
        void  set_Uniform(const std::string& name, glm::vec2 value);
        void  set_Uniform(const std::string& name, float x, float y, float z);
        void  set_Uniform(const std::string& name, glm::vec3 value);
        void  set_Uniform(const std::string& name, float x, float y, float z, float w);
        void  set_Uniform(const std::string& name, glm::vec4 value);
        void  set_Uniform(const std::string& name, glm::mat2 value);
        void  set_Uniform(const std::string& name, glm::mat3 value);
        void  set_Uniform(const std::string& name, glm::mat4 value);
        void  set_Uniform(const std::string& name, float value);
        void  set_Uniform(const std::string& name,   int value);
        void  set_Uniform(const std::string& name,  bool value);

        void  set_Texture(std::string name, Texture* value, unsigned int unit = 0);
        //void  set_Texture_cube(std::string name, TextureCube* value, unsigned int unit = 0);
        void  set_properties(e_simple_props prop);

        std::map<std::string, Uniform_value>* get_Uniforms() { return &m_Uniforms; }
        std::map<std::string, Uniform_value_sampler>* get_Sampler_uniforms() { return &m_Sampler_uniforms; }

    private:
                                              Shader& m_Shader;
                std::map<std::string, Uniform_value>  m_Uniforms;
        std::map<std::string, Uniform_value_sampler>  m_Sampler_uniforms;
    };
}
#endif //__MATERIAL_H_