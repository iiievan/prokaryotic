#include "Cube.h"

static std::vector<Vertex> cube_vertices =
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

std::vector<GLuint> cube_indices =
{
    //Top
    2, 6, 7,
    2, 3, 7,

    //Bottom
    0, 4, 5,
    0, 1, 5,

    //Left
    0, 2, 6,
    0, 4, 6,

    //Right
    1, 3, 7,
    1, 5, 7,

    //Front
    0, 2, 3,
    0, 1, 3,

    //Back
    4, 6, 7,
    4, 5, 7
};

Cube::Cube()
: PROKARYOTIC::Mesh<Vertex>(&cube_vertices, nullptr)
{
    
}