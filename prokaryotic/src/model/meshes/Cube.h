#ifndef __CUBE_H
#define __CUBE_H

#include <glm/glm.hpp>
#include "model/Mesh.h"
#include "model/Vertex.h"

namespace PROKARYOTIC
{
	template <typename T> class Mesh;
	class Vertex;

	extern std::vector<Vertex> cube_vertices;
	extern std::vector<GLuint> cube_indices;

	template <typename T>
	class Cube : public Mesh<T>
	{
	public:
		Cube()
		:Mesh<T>(&cube_vertices, nullptr)	// draw with VAO
		{}
		~Cube() {}
	};
}

#endif	//__CUBE_H
