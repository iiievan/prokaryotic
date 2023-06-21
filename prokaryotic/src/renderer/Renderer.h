#ifndef __RENDERER_H
#define __RENDERER_H

#include<vector>
#include "model/Mesh.h"
#include "model/Material.h"
#include "scene/Scene_object.h"
#include "light/Light_source.h"
#include "camera/Camera.h"

namespace PROKARYOTIC
{
	template <typename T> class Mesh;
	class Material;
	class Render_object;
	class Scene_object;
	class Light_source;
	class UI_item;
	class Camera;

	class Renderer
	{
	public:
		      Renderer() {}
		     ~Renderer() {}

		void  push_to_render(Render_object* p_object);
		void  push_to_render(Scene_object* p_object);
		void  push_to_render(Light_source* p_object);
		void  push_to_render(UI_item* p_object);

		void  process_objects(Camera* p_camera = nullptr);

	private:
		void  m_handle_scene_object(Scene_object& scene_object, Camera* p_camera);
		void  m_handle_light_object(Light_source& light_obj, Camera* p_camera);

		std::vector<Render_object*> m_render_objects;
	};
}
#endif //__RENDERER_H