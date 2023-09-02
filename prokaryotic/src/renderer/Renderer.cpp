#include"renderer/Renderer.h"

namespace PROKARYOTIC
{
    void  Renderer::push_to_render(Render_object* p_object)
    {
        m_render_objects.push_back(p_object);
    }

    void  Renderer::push_to_render(Scene_object* p_object)
    {
        Render_object* p_render_obj = dynamic_cast<Render_object*>(p_object);

        if (p_render_obj == nullptr)
            printf("push to render: Scene_object to Render object bad cast!");
        else
            m_render_objects.push_back(p_render_obj);
    }

    void  Renderer::push_to_render(Light_source* p_object)
    {
        Render_object* p_render_obj = dynamic_cast<Render_object*>(p_object);

        if (p_render_obj == nullptr)
            printf("push to render: Light_source to Render object bad cast!");
        else
            m_render_objects.push_back(p_render_obj);
    }

    void  Renderer::process_objects(Camera* p_camera)
    {
        e_RENDER_OBJECT_TYPES obj_type = TYPE_NA;

        for (auto& it : m_render_objects)
        {
            obj_type = it->get_render_object_TYPE();
            switch (obj_type)
            {
                case TYPE_SCENE_OBJECT:
                    try
                    {
                        Scene_object& scene_obj = dynamic_cast<Scene_object&>(*it);
                        m_handle_scene_object(scene_obj, p_camera);
                    }
                    catch (std::bad_cast)
                    {
                        printf("rendering: Scene_object to Render object bad cast!");
                    }
                    break;
                case TYPE_LIGHT_SOURCE:                    
                    try
                    {
                        Light_source& light_obj = dynamic_cast<Light_source&>(*it);
                        m_handle_light_object(light_obj, p_camera);
                    }
                    catch (std::bad_cast)
                    {
                        printf("rendering: Light_source to Render object bad cast!");
                    }
                    break;
                case TYPE_NA:
                default:
                    break;
            }
        }
    }

    void  Renderer::m_handle_scene_object(Scene_object& scene_obj, Camera* p_camera)
    {
        scene_obj.p_material->get_Shader().use();

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
                scene_obj.p_material->get_Shader().set_Uniform(u_it->first, u_it->second.Bool);
                break;
            case UNIFORM_TYPE_INT:
                scene_obj.p_material->get_Shader().set_Uniform(u_it->first, u_it->second.Int);
                break;
            case UNIFORM_TYPE_FLOAT:
                scene_obj.p_material->get_Shader().set_Uniform(u_it->first, u_it->second.Float);
                break;
            case UNIFORM_TYPE_VEC2:
                scene_obj.p_material->get_Shader().set_Uniform(u_it->first, u_it->second.Vec2);
                break;
            case UNIFORM_TYPE_VEC3:
                scene_obj.p_material->get_Shader().set_Uniform(u_it->first, u_it->second.Vec3);
                break;
            case UNIFORM_TYPE_VEC4:
                scene_obj.p_material->get_Shader().set_Uniform(u_it->first, u_it->second.Vec4);
                break;
            case UNIFORM_TYPE_MAT2:
                scene_obj.p_material->get_Shader().set_Uniform(u_it->first, u_it->second.Mat2);
                break;
            case UNIFORM_TYPE_MAT3:
                scene_obj.p_material->get_Shader().set_Uniform(u_it->first, u_it->second.Mat3);
                break;
            case UNIFORM_TYPE_MAT4:
                scene_obj.p_material->get_Shader().set_Uniform(u_it->first, u_it->second.Mat4);
                break;
            default:
                printf("Unrecognized Uniform type set.");
                break;
            }
        }

        scene_obj.p_mesh->draw<Shader>(nullptr);
    }

    void  Renderer::m_handle_light_object(Light_source& light_obj, Camera* p_camera)
    {
        light_obj.get_Shader_program().use();

        if (p_camera != nullptr)
        {
            light_obj.set_Matrix("projection", p_camera->Projection);
            light_obj.set_Matrix("view", p_camera->View);
        }

        light_obj.set_Matrix("model", light_obj.get_Transform());

        // set uniform state of material
        auto* uniforms = light_obj.get_Uniforms();
        for (auto u_it = uniforms->begin(); u_it != uniforms->end(); ++u_it)
        {
            switch (u_it->second.Type)
            {
            case UNIFORM_TYPE_BOOL:
                light_obj.get_Shader_program().set_Uniform(u_it->first, u_it->second.Bool);
                break;
            case UNIFORM_TYPE_INT:
                light_obj.get_Shader_program().set_Uniform(u_it->first, u_it->second.Int);
                break;
            case UNIFORM_TYPE_FLOAT:
                light_obj.get_Shader_program().set_Uniform(u_it->first, u_it->second.Float);
                break;
            case UNIFORM_TYPE_VEC2:
                light_obj.get_Shader_program().set_Uniform(u_it->first, u_it->second.Vec2);
                break;
            case UNIFORM_TYPE_VEC3:
                light_obj.get_Shader_program().set_Uniform(u_it->first, u_it->second.Vec3);
                break;
            case UNIFORM_TYPE_VEC4:
                light_obj.get_Shader_program().set_Uniform(u_it->first, u_it->second.Vec4);
                break;
            case UNIFORM_TYPE_MAT2:
                light_obj.get_Shader_program().set_Uniform(u_it->first, u_it->second.Mat2);
                break;
            case UNIFORM_TYPE_MAT3:
                light_obj.get_Shader_program().set_Uniform(u_it->first, u_it->second.Mat3);
                break;
            case UNIFORM_TYPE_MAT4:
                light_obj.get_Shader_program().set_Uniform(u_it->first, u_it->second.Mat4);
                break;
            default:
                printf("Unrecognized Uniform type set.");
                break;
            }
        }

        light_obj.draw<Shader>(nullptr);
    }    
}