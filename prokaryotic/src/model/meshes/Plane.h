#ifndef __PLANE_H
#define __PLANE_H

#include <glm/glm.hpp>
#include "model/Mesh.h"
#include "model/Vertex.h"

namespace PROKARYOTIC
{
    template <typename T> class Mesh_2D;
    class Vertex;

    extern std::vector<Vertex> rectangle_vertices;
    extern std::vector<GLuint> rectangle_indices;

	template <typename T>
	class Plane : public Mesh_2D<T>
	{
	public:
		Plane()
		: Mesh_2D<T>(&rectangle_vertices, &rectangle_indices)  // draw with VAO
		{}
		~Plane() {}
	};
}

#endif	//__PLANE_H
