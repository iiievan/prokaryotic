#include "Cube.h"

std::vector<Vertex> cube_vertices =
{
           //  vertices                     // UVs                  // normals
    Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 0.0f),  glm::vec3( 0.0f,  0.0f, -1.0f)),
    Vertex(glm::vec3( 0.5f, -0.5f, -0.5f),  glm::vec2(1.0f, 0.0f),  glm::vec3( 0.0f,  0.0f, -1.0f)),
    Vertex(glm::vec3( 0.5f,  0.5f, -0.5f),  glm::vec2(1.0f, 1.0f),  glm::vec3( 0.0f,  0.0f, -1.0f)),
    Vertex(glm::vec3( 0.5f,  0.5f, -0.5f),  glm::vec2(1.0f, 1.0f),  glm::vec3( 0.0f,  0.0f, -1.0f)),
    Vertex(glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec2(0.0f, 1.0f),  glm::vec3( 0.0f,  0.0f, -1.0f)),
    Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 0.0f),  glm::vec3( 0.0f,  0.0f, -1.0f)),
                                                                                           
    Vertex(glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec2(0.0f, 0.0f),  glm::vec3( 0.0f,  0.0f,  1.0f)),
    Vertex(glm::vec3( 0.5f, -0.5f,  0.5f),  glm::vec2(1.0f, 0.0f),  glm::vec3( 0.0f,  0.0f,  1.0f)),
    Vertex(glm::vec3( 0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 1.0f),  glm::vec3( 0.0f,  0.0f,  1.0f)),
    Vertex(glm::vec3( 0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 1.0f),  glm::vec3( 0.0f,  0.0f,  1.0f)),
    Vertex(glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec2(0.0f, 1.0f),  glm::vec3( 0.0f,  0.0f,  1.0f)),
    Vertex(glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec2(0.0f, 0.0f),  glm::vec3( 0.0f,  0.0f,  1.0f)),
                                                                                            
    Vertex(glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f),  glm::vec3(-1.0f,  0.0f,  0.0f)),
    Vertex(glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec2(1.0f, 1.0f),  glm::vec3(-1.0f,  0.0f,  0.0f)),
    Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 1.0f),  glm::vec3(-1.0f,  0.0f,  0.0f)),
    Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 1.0f),  glm::vec3(-1.0f,  0.0f,  0.0f)),
    Vertex(glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec2(0.0f, 0.0f),  glm::vec3(-1.0f,  0.0f,  0.0f)),
    Vertex(glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f),  glm::vec3(-1.0f,  0.0f,  0.0f)),
                                                                                            
    Vertex(glm::vec3( 0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f),  glm::vec3( 1.0f,  0.0f,  0.0f)),
    Vertex(glm::vec3( 0.5f,  0.5f, -0.5f),  glm::vec2(1.0f, 1.0f),  glm::vec3( 1.0f,  0.0f,  0.0f)),
    Vertex(glm::vec3( 0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 1.0f),  glm::vec3( 1.0f,  0.0f,  0.0f)),
    Vertex(glm::vec3( 0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 1.0f),  glm::vec3( 1.0f,  0.0f,  0.0f)),
    Vertex(glm::vec3( 0.5f, -0.5f,  0.5f),  glm::vec2(0.0f, 0.0f),  glm::vec3( 1.0f,  0.0f,  0.0f)),
    Vertex(glm::vec3( 0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f),  glm::vec3( 1.0f,  0.0f,  0.0f)),
                                                                                            
    Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 1.0f),  glm::vec3( 0.0f, -1.0f,  0.0f)),
    Vertex(glm::vec3( 0.5f, -0.5f, -0.5f),  glm::vec2(1.0f, 1.0f),  glm::vec3( 0.0f, -1.0f,  0.0f)),
    Vertex(glm::vec3( 0.5f, -0.5f,  0.5f),  glm::vec2(1.0f, 0.0f),  glm::vec3( 0.0f, -1.0f,  0.0f)),
    Vertex(glm::vec3( 0.5f, -0.5f,  0.5f),  glm::vec2(1.0f, 0.0f),  glm::vec3( 0.0f, -1.0f,  0.0f)),
    Vertex(glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec2(0.0f, 0.0f),  glm::vec3( 0.0f, -1.0f,  0.0f)),
    Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 1.0f),  glm::vec3( 0.0f, -1.0f,  0.0f)),
                                                                                            
    Vertex(glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec2(0.0f, 1.0f),  glm::vec3( 0.0f,  1.0f,  0.0f)),
    Vertex(glm::vec3( 0.5f,  0.5f, -0.5f),  glm::vec2(1.0f, 1.0f),  glm::vec3( 0.0f,  1.0f,  0.0f)),
    Vertex(glm::vec3( 0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f),  glm::vec3( 0.0f,  1.0f,  0.0f)),
    Vertex(glm::vec3( 0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f),  glm::vec3( 0.0f,  1.0f,  0.0f)),
    Vertex(glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec2(0.0f, 0.0f),  glm::vec3( 0.0f,  1.0f,  0.0f)),
    Vertex(glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec2(0.0f, 1.0f),  glm::vec3( 0.0f,  1.0f,  0.0f))
};


Cube::Cube()
: Mesh(cube_vertices, cube_indices)
{
    
}