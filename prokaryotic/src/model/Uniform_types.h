#ifndef __UNIFORM_TYPES_H
#define __UNIFORM_TYPES_H

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace PROKARYOTIC
{
    class Texture;
    //class TextureCube;

    enum e_UNIFORM_TYPE : uint32_t
    {
        UNIFORM_TYPE_BOOL,
        UNIFORM_TYPE_INT,
        UNIFORM_TYPE_FLOAT,
        UNIFORM_TYPE_SAMPLER1D,
        UNIFORM_TYPE_SAMPLER2D,
        UNIFORM_TYPE_SAMPLER3D,
        UNIFORM_TYPE_SAMPLERCUBE,
        UNIFORM_TYPE_VEC2,
        UNIFORM_TYPE_VEC3,
        UNIFORM_TYPE_VEC4,
        UNIFORM_TYPE_MAT2,
        UNIFORM_TYPE_MAT3,
        UNIFORM_TYPE_MAT4,
    };

    struct Uniform
    {
        e_UNIFORM_TYPE  Type;
        std::string  Name;
        int  Size;
        unsigned int  Location;
    };

    struct Uniform_value
    {
        e_UNIFORM_TYPE Type;
        // TODO: now each element takes up the space of its largest 
        // element (mat4) which is 64 bytes; come up with a better solution!
        union
        {
            bool  Bool;
            int  Int;
            float  Float;

            glm::vec2  Vec2;
            glm::vec3  Vec3;
            glm::vec4  Vec4;
            glm::mat2  Mat2;
            glm::mat3  Mat3;
            glm::mat4  Mat4;
        };
    };

    struct Uniform_value_sampler
    {
        e_UNIFORM_TYPE  Type;
        unsigned int  Unit;

        union
        {
            Texture* Texture;
            //        TextureCube *Texture_cube;
        };
    };

    struct Vertex_attribute
    {
        e_UNIFORM_TYPE  Type;
        std::string  Name;
        int  Size;
        unsigned int  Location;
    };
}
#endif