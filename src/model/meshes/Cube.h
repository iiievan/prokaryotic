#ifndef __CUBE_H
#define __CUBE_H

#include <glm/glm.hpp>
#include "model/Mesh.h"

class Cube : public PROKARYOTIC::Mesh<Vertex>
{
public:
	 Cube();
	~Cube() {}
};

#endif	//__CUBE_H
