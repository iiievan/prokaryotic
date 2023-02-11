#ifndef __RENDERER_H
#define __RENDERER_H

#include<vector>
#include "model/Mesh.h"
#include "model/Material.h"
#include "scene/Scene_object.h"

class Mesh;
class Material;
class Scene_object;

struct Renderer_object
{
	    Mesh* p_mesh;
	Material* p_material;

	Renderer_object(Mesh* mesh, Material* mat) :p_mesh(mesh), p_material(mat) {}
};

class Renderer
{
public:
			Renderer() {}
		   ~Renderer() {}

      void  Push_render(Mesh* p_mesh, Material* p_material);
      void  Push_render(Renderer_object object);
	  void  Push_render(Scene_object* p_object);
				 
	  void  Render_pushed_objects();

	  std::vector<Renderer_object> m_objects_buffer;
};

#endif //__RENDERER_H