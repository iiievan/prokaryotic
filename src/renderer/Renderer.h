#ifndef __RENDERER_H
#define __RENDERER_H

#include<vector>
#include "model/Mesh.h"
#include "model/Material.h"
#include "scene/Scene_object.h"

class Mesh;
class Material;
class Scene_object;

class Renderer
{
public:
			Renderer() {}
		   ~Renderer() {}

      void  push_to_render(Mesh* p_mesh, Material* p_material);
	  void  push_to_render(Scene_object* p_object);
				 
	  void  process_objects();

	  std::vector<Scene_object*> m_render_objects;
};

#endif //__RENDERER_H