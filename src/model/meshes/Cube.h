#ifndef __CUBE_H
#define __CUBE_H

#include <glm/glm.hpp>
#include "model/Mesh.h"

static std::vector<Vertex> cube_vertices;

class Cube : public Mesh
{
public:
	 Cube();
	~Cube() {}
};

#endif	//__CUBE_H
