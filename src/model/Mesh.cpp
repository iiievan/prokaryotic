#include "Mesh.h"


std::vector<Simple_vertex> triangle_vertices =
{
    Simple_vertex(-0.51f, -0.51f, 0.0f),
    Simple_vertex(-0.26f, 0.0f, 0.0f),
    Simple_vertex(0.0f,  -0.51f, 0.0f)
};

std::vector<Simple_vertex> triangle2_vertices =
{
    Simple_vertex(-0.24f, 0.0f, 0.0f),
    Simple_vertex(0.02f, -0.51f, 0.0f),
    Simple_vertex(0.26f,  0.0f, 0.0f)
};

std::vector<Vertex> rectangle_vertices =
{
    //  vertices                           // UVs                 // normals
    Vertex(glm::vec3(0.5f,  0.5f, 0.0f),  glm::vec2(1.0f,1.0f),  glm::vec3(1.0f, 0.0f, 0.0f)),
    Vertex(glm::vec3(0.5f, -0.5f, 0.0f),  glm::vec2(1.0f,0.0f),  glm::vec3(0.0f, 1.0f, 0.0f)),
    Vertex(glm::vec3(-0.5f, -0.5f, 0.0f),  glm::vec2(0.0f,0.0f),  glm::vec3(0.0f, 0.0f, 1.0f)),
    Vertex(glm::vec3(-0.5f,  0.5f, 0.0f),  glm::vec2(0.0f,1.0f),  glm::vec3(1.0f, 1.0f, 0.0f))
};

std::vector<Vertex> coloured_triangle =
{
    Vertex(glm::vec3(0.5f, -0.5f, 0.0f),  glm::vec2(0.0f,0.0f), glm::vec3(1.0f, 0.0f, 0.0f)),
    Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(1.0f,0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
    Vertex(glm::vec3(0.0f,  0.5f, 0.0f),  glm::vec2(0.5f,1.0f), glm::vec3(0.0f, 0.0f, 1.0f))
};

std::vector<unsigned int> rectangle_indices =
{
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

std::vector<unsigned int> triangle_indices =
{
    0, 1, 2
};
