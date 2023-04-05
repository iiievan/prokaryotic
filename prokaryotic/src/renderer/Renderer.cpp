#include"renderer/Renderer.h"

namespace PROKARYOTIC
{

    void  Renderer::push_to_render(Mesh<Vertex>* p_mesh, Material* p_material)
    {
        Scene_object* object = new Scene_object(p_mesh, p_material);

        m_render_objects.push_back(object);
    }

    void  Renderer::push_to_render(Scene_object* p_object)
    {
        m_render_objects.push_back(p_object);
    }

    void  Renderer::process_objects(Camera* p_camera)
    {
        for (auto& it : m_render_objects)
        {
            it->p_material->get_Shader_program()->use();

            if (p_camera != nullptr)
            {
                it->p_material->set_Matrix("view", p_camera->View);
                it->p_material->set_Matrix("projection", p_camera->Projection);
                it->p_material->set_Matrix("cam_position", p_camera->get_Position());
            }

            it->p_material->set_Matrix("model", it->get_Transform());

            // bind/active uniform sampler/texture objects
            auto* samplers = it->p_material->get_Sampler_uniforms();

            for (auto sampler_it = samplers->begin(); sampler_it != samplers->end(); ++sampler_it)
            {
                sampler_it->second.Texture->Bind(sampler_it->second.Unit);
            }

            // set uniform state of material
            auto* uniforms = it->p_material->get_Uniforms();
            for (auto u_it = uniforms->begin(); u_it != uniforms->end(); ++u_it)
            {
                switch (u_it->second.Type)
                {
                case UNIFORM_TYPE_BOOL:
                    it->p_material->get_Shader_program()->set_Uniform(u_it->first, u_it->second.Bool);
                    break;
                case UNIFORM_TYPE_INT:
                    it->p_material->get_Shader_program()->set_Uniform(u_it->first, u_it->second.Int);
                    break;
                case UNIFORM_TYPE_FLOAT:
                    it->p_material->get_Shader_program()->set_Uniform(u_it->first, u_it->second.Float);
                    break;
                case UNIFORM_TYPE_VEC2:
                    it->p_material->get_Shader_program()->set_Uniform(u_it->first, u_it->second.Vec2);
                    break;
                case UNIFORM_TYPE_VEC3:
                    it->p_material->get_Shader_program()->set_Uniform(u_it->first, u_it->second.Vec3);
                    break;
                case UNIFORM_TYPE_VEC4:
                    it->p_material->get_Shader_program()->set_Uniform(u_it->first, u_it->second.Vec4);
                    break;
                case UNIFORM_TYPE_MAT2:
                    it->p_material->get_Shader_program()->set_Uniform(u_it->first, u_it->second.Mat2);
                    break;
                case UNIFORM_TYPE_MAT3:
                    it->p_material->get_Shader_program()->set_Uniform(u_it->first, u_it->second.Mat3);
                    break;
                case UNIFORM_TYPE_MAT4:
                    it->p_material->get_Shader_program()->set_Uniform(u_it->first, u_it->second.Mat4);
                    break;
                default:
                    printf("Unrecognized Uniform type set.");
                    break;
                }
            }

            it->p_mesh->draw<Shader_program>(nullptr);
        }
    }
}