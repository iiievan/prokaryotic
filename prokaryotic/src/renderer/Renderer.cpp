#include"renderer/Renderer.h"

namespace PROKARYOTIC
{

    void  Renderer::push_to_render(Mesh<Vertex>* p_mesh, Material* p_material)
    {
        Scene_object* p_scene_obj = new Scene_object(p_mesh, p_material);

        Render_object* p_render_obj = dynamic_cast<Render_object*>(p_scene_obj);

        m_render_objects.push_back(p_render_obj);
    }

    void  Renderer::push_to_render(Render_object* p_object)
    {
        m_render_objects.push_back(p_object);
    }

    void  Renderer::push_to_render(Scene_object* p_object)
    {
        Render_object* p_render_obj = dynamic_cast<Render_object*>(p_object);

        m_render_objects.push_back(p_object);
    }

    void  Renderer::process_objects(Camera* p_camera)
    {
        for (auto& it : m_render_objects)
        {
            if (it->get_render_object_TYPE() == TYPE_SCENE_OBJECT)
            {                
                Scene_object& scene_obj = dynamic_cast<Scene_object&>(*it);

                scene_obj.p_material->get_Shader_program()->use();

                if (p_camera != nullptr)
                {
                    scene_obj.p_material->set_Matrix("projection", p_camera->Projection);
                    scene_obj.p_material->set_Matrix("view", p_camera->View);
                }

                scene_obj.p_material->set_Matrix("model", scene_obj.get_Transform());

                // bind/active uniform sampler/texture objects
                auto* samplers = scene_obj.p_material->get_Sampler_uniforms();

                for (auto sampler_it = samplers->begin(); sampler_it != samplers->end(); ++sampler_it)
                {
                    sampler_it->second.Texture->Bind(sampler_it->second.Unit);
                }

                // set uniform state of material
                auto* uniforms = scene_obj.p_material->get_Uniforms();
                for (auto u_it = uniforms->begin(); u_it != uniforms->end(); ++u_it)
                {
                    switch (u_it->second.Type)
                    {
                    case UNIFORM_TYPE_BOOL:
                        scene_obj.p_material->get_Shader_program()->set_Uniform(u_it->first, u_it->second.Bool);
                        break;
                    case UNIFORM_TYPE_INT:
                        scene_obj.p_material->get_Shader_program()->set_Uniform(u_it->first, u_it->second.Int);
                        break;
                    case UNIFORM_TYPE_FLOAT:
                        scene_obj.p_material->get_Shader_program()->set_Uniform(u_it->first, u_it->second.Float);
                        break;
                    case UNIFORM_TYPE_VEC2:
                        scene_obj.p_material->get_Shader_program()->set_Uniform(u_it->first, u_it->second.Vec2);
                        break;
                    case UNIFORM_TYPE_VEC3:
                        scene_obj.p_material->get_Shader_program()->set_Uniform(u_it->first, u_it->second.Vec3);
                        break;
                    case UNIFORM_TYPE_VEC4:
                        scene_obj.p_material->get_Shader_program()->set_Uniform(u_it->first, u_it->second.Vec4);
                        break;
                    case UNIFORM_TYPE_MAT2:
                        scene_obj.p_material->get_Shader_program()->set_Uniform(u_it->first, u_it->second.Mat2);
                        break;
                    case UNIFORM_TYPE_MAT3:
                        scene_obj.p_material->get_Shader_program()->set_Uniform(u_it->first, u_it->second.Mat3);
                        break;
                    case UNIFORM_TYPE_MAT4:
                        scene_obj.p_material->get_Shader_program()->set_Uniform(u_it->first, u_it->second.Mat4);
                        break;
                    default:
                        printf("Unrecognized Uniform type set.");
                        break;
                    }
                }

                scene_obj.p_mesh->draw<Shader_program>(nullptr);
            }
        }
    }
}