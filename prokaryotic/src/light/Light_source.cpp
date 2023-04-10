#include "light/Light_source.h"
namespace PROKARYOTIC
{
	std::vector<Simple_vertex> light_cube_vertices =
	{
		//  only positions                            
		Simple_vertex(glm::vec3(-0.5f, -0.5f, -0.5f)),
		Simple_vertex(glm::vec3( 0.5f, -0.5f, -0.5f)),
		Simple_vertex(glm::vec3( 0.5f,  0.5f, -0.5f)),
		Simple_vertex(glm::vec3( 0.5f,  0.5f, -0.5f)),
		Simple_vertex(glm::vec3(-0.5f,  0.5f, -0.5f)),
		Simple_vertex(glm::vec3(-0.5f, -0.5f, -0.5f)),

		Simple_vertex(glm::vec3(-0.5f, -0.5f,  0.5f)),
		Simple_vertex(glm::vec3( 0.5f, -0.5f,  0.5f)),
		Simple_vertex(glm::vec3( 0.5f,  0.5f,  0.5f)),
		Simple_vertex(glm::vec3( 0.5f,  0.5f,  0.5f)),
		Simple_vertex(glm::vec3(-0.5f,  0.5f,  0.5f)),
		Simple_vertex(glm::vec3(-0.5f, -0.5f,  0.5f)),

		Simple_vertex(glm::vec3(-0.5f,  0.5f,  0.5f)),
		Simple_vertex(glm::vec3(-0.5f,  0.5f, -0.5f)),
		Simple_vertex(glm::vec3(-0.5f, -0.5f, -0.5f)),
		Simple_vertex(glm::vec3(-0.5f, -0.5f, -0.5f)),
		Simple_vertex(glm::vec3(-0.5f, -0.5f,  0.5f)),
		Simple_vertex(glm::vec3(-0.5f,  0.5f,  0.5f)),

		Simple_vertex(glm::vec3( 0.5f,  0.5f,  0.5f)),
		Simple_vertex(glm::vec3( 0.5f,  0.5f, -0.5f)),
		Simple_vertex(glm::vec3( 0.5f, -0.5f, -0.5f)),
		Simple_vertex(glm::vec3( 0.5f, -0.5f, -0.5f)),
		Simple_vertex(glm::vec3( 0.5f, -0.5f,  0.5f)),
		Simple_vertex(glm::vec3( 0.5f,  0.5f,  0.5f)),

		Simple_vertex(glm::vec3(-0.5f, -0.5f, -0.5f)),
		Simple_vertex(glm::vec3( 0.5f, -0.5f, -0.5f)),
		Simple_vertex(glm::vec3( 0.5f, -0.5f,  0.5f)),
		Simple_vertex(glm::vec3( 0.5f, -0.5f,  0.5f)),
		Simple_vertex(glm::vec3(-0.5f, -0.5f,  0.5f)),
		Simple_vertex(glm::vec3(-0.5f, -0.5f, -0.5f)),

		Simple_vertex(glm::vec3(-0.5f,  0.5f, -0.5f)),
		Simple_vertex(glm::vec3(0.5f,  0.5f, -0.5f)),
		Simple_vertex(glm::vec3(0.5f,  0.5f,  0.5f)),
		Simple_vertex(glm::vec3(0.5f,  0.5f,  0.5f)),
		Simple_vertex(glm::vec3(-0.5f,  0.5f,  0.5f)),
		Simple_vertex(glm::vec3(-0.5f,  0.5f, -0.5f))
	};
}
