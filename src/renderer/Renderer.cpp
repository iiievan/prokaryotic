#include"renderer/Renderer.h"

void  Renderer::Push_render(Mesh* p_mesh, Material* p_material)
{
    Renderer_object object(p_mesh, p_material);

	m_objects_buffer.push_back(object);
}

void  Renderer::Push_render(Renderer_object object)
{
    m_objects_buffer.push_back(object);
}

void  Renderer::Push_render(Scene_object* p_object)
{
	return;
}

void  Renderer::Render_pushed_objects()
{
	for (auto& it : m_objects_buffer)
	{
		it.p_material->get_Shader_program()->use();

        // bind/active uniform sampler/texture objects
        auto* samplers = it.p_material->get_Sampler_uniforms();

        for (auto sampler_it = samplers->begin(); sampler_it != samplers->end(); ++sampler_it)
        {
			sampler_it->second.Texture->Bind(sampler_it->second.Unit);
        }

        // set uniform state of material
        auto* uniforms = it.p_material->get_Uniforms();
        for (auto u_it = uniforms->begin(); u_it != uniforms->end(); ++u_it)
        {
            switch (u_it->second.Type)
            {
            case UNIFORM_TYPE_BOOL:
                it.p_material->get_Shader_program()->set_Uniform(u_it->first, u_it->second.Bool);
                break;
            case UNIFORM_TYPE_INT:
                it.p_material->get_Shader_program()->set_Uniform(u_it->first, u_it->second.Int);
                break;
            case UNIFORM_TYPE_FLOAT:
                it.p_material->get_Shader_program()->set_Uniform(u_it->first, u_it->second.Float);
                break;
            case UNIFORM_TYPE_VEC2:
                it.p_material->get_Shader_program()->set_Uniform(u_it->first, u_it->second.Vec2);
                break;
            case UNIFORM_TYPE_VEC3:
                it.p_material->get_Shader_program()->set_Uniform(u_it->first, u_it->second.Vec3);
                break;
            case UNIFORM_TYPE_VEC4:
                it.p_material->get_Shader_program()->set_Uniform(u_it->first, u_it->second.Vec4);
                break;
            case UNIFORM_TYPE_MAT2:
                it.p_material->get_Shader_program()->set_Uniform(u_it->first, u_it->second.Mat2);
                break;
            case UNIFORM_TYPE_MAT3:
                it.p_material->get_Shader_program()->set_Uniform(u_it->first, u_it->second.Mat3);
                break;
            case UNIFORM_TYPE_MAT4:
                it.p_material->get_Shader_program()->set_Uniform(u_it->first, u_it->second.Mat4);
                break;
            default:
                printf("Unrecognized Uniform type set.");
                break;
            }
        }

        it.p_mesh->draw_with_EBO(nullptr);
	}
}