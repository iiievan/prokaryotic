#include "Cube.h"

static std::vector<glm::vec3> vertices =
std::vector<glm::vec3> 
{
    glm::vec3(-0.5f, -0.5f, -0.5f),
    glm::vec3( 0.5f, -0.5f, -0.5f),
    glm::vec3( 0.5f,  0.5f, -0.5f),
    glm::vec3( 0.5f,  0.5f, -0.5f),
    glm::vec3(-0.5f,  0.5f, -0.5f),
    glm::vec3(-0.5f, -0.5f, -0.5f),

    glm::vec3(-0.5f, -0.5f,  0.5f),
    glm::vec3( 0.5f, -0.5f,  0.5f),
    glm::vec3( 0.5f,  0.5f,  0.5f),
    glm::vec3( 0.5f,  0.5f,  0.5f),
    glm::vec3(-0.5f,  0.5f,  0.5f),
    glm::vec3(-0.5f, -0.5f,  0.5f),

    glm::vec3(-0.5f,  0.5f,  0.5f), 
    glm::vec3(-0.5f,  0.5f, -0.5f), 
    glm::vec3(-0.5f, -0.5f, -0.5f), 
    glm::vec3(-0.5f, -0.5f, -0.5f), 
    glm::vec3(-0.5f, -0.5f,  0.5f), 
    glm::vec3(-0.5f,  0.5f,  0.5f), 

    glm::vec3( 0.5f,  0.5f,  0.5f), 
    glm::vec3( 0.5f,  0.5f, -0.5f), 
    glm::vec3( 0.5f, -0.5f, -0.5f), 
    glm::vec3( 0.5f, -0.5f, -0.5f), 
    glm::vec3( 0.5f, -0.5f,  0.5f), 
    glm::vec3( 0.5f,  0.5f,  0.5f), 

    glm::vec3(-0.5f, -0.5f, -0.5f), 
    glm::vec3( 0.5f, -0.5f, -0.5f), 
    glm::vec3( 0.5f, -0.5f,  0.5f), 
    glm::vec3( 0.5f, -0.5f,  0.5f), 
    glm::vec3(-0.5f, -0.5f,  0.5f), 
    glm::vec3(-0.5f, -0.5f, -0.5f), 

    glm::vec3(-0.5f,  0.5f, -0.5f), 
    glm::vec3( 0.5f,  0.5f, -0.5f), 
    glm::vec3( 0.5f,  0.5f,  0.5f), 
    glm::vec3( 0.5f,  0.5f,  0.5f), 
    glm::vec3(-0.5f,  0.5f,  0.5f), 
    glm::vec3(-0.5f,  0.5f, -0.5f), 
};

static std::vector<glm::vec2> uv = 
std::vector<glm::vec2>
{
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),
    glm::vec2(0.0f, 0.0f),

    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),
    glm::vec2(0.0f, 0.0f),

    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),

    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),

    glm::vec2(0.0f, 1.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(0.0f, 0.0f),
    glm::vec2(0.0f, 1.0f),

    glm::vec2(0.0f, 1.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(0.0f, 0.0f),
    glm::vec2(0.0f, 1.0f)
};

static std::vector<glm::vec3>  normals = 
std::vector<glm::vec3>
{
   glm::vec3( 0.0f,  0.0f, -1.0f),
   glm::vec3( 0.0f,  0.0f, -1.0f),
   glm::vec3( 0.0f,  0.0f, -1.0f),
   glm::vec3( 0.0f,  0.0f, -1.0f),
   glm::vec3( 0.0f,  0.0f, -1.0f),
   glm::vec3( 0.0f,  0.0f, -1.0f),

   glm::vec3( 0.0f,  0.0f,  1.0f),
   glm::vec3( 0.0f,  0.0f,  1.0f),
   glm::vec3( 0.0f,  0.0f,  1.0f),
   glm::vec3( 0.0f,  0.0f,  1.0f),
   glm::vec3( 0.0f,  0.0f,  1.0f),
   glm::vec3( 0.0f,  0.0f,  1.0f),

   glm::vec3(-1.0f,  0.0f,  0.0f),
   glm::vec3(-1.0f,  0.0f,  0.0f),
   glm::vec3(-1.0f,  0.0f,  0.0f),
   glm::vec3(-1.0f,  0.0f,  0.0f),
   glm::vec3(-1.0f,  0.0f,  0.0f),
   glm::vec3(-1.0f,  0.0f,  0.0f),

   glm::vec3( 1.0f,  0.0f,  0.0f),
   glm::vec3( 1.0f,  0.0f,  0.0f),
   glm::vec3( 1.0f,  0.0f,  0.0f),
   glm::vec3( 1.0f,  0.0f,  0.0f),
   glm::vec3( 1.0f,  0.0f,  0.0f),
   glm::vec3( 1.0f,  0.0f,  0.0f),

   glm::vec3( 0.0f, -1.0f,  0.0f),
   glm::vec3( 0.0f, -1.0f,  0.0f),
   glm::vec3( 0.0f, -1.0f,  0.0f),
   glm::vec3( 0.0f, -1.0f,  0.0f),
   glm::vec3( 0.0f, -1.0f,  0.0f),
   glm::vec3( 0.0f, -1.0f,  0.0f),

   glm::vec3( 0.0f,  1.0f,  0.0f),
   glm::vec3( 0.0f,  1.0f,  0.0f),
   glm::vec3( 0.0f,  1.0f,  0.0f),
   glm::vec3( 0.0f,  1.0f,  0.0f),
   glm::vec3( 0.0f,  1.0f,  0.0f),
   glm::vec3( 0.0f,  1.0f,  0.0f),
};

Cube::Cube()
{
    
}