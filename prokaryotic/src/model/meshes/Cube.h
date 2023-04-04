#ifndef __CUBE_H
#define __CUBE_H

#include <glm/glm.hpp>
#include "model/Mesh.h"
#include "model/Vertex.h"

namespace PROKARYOTIC
{
	template <typename T> class Mesh;
	class Vertex;

	std::vector<Vertex> cube_vertices;
	std::vector<GLuint> cube_indices;

	class Cube : public Mesh<Vertex>
	{
	public:
		Cube()
		:Mesh<Vertex>(&cube_vertices, nullptr) {}
		~Cube() {}
	};
}

#endif	//__CUBE_H
