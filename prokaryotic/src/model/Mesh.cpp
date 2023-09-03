#include "model/Mesh.h"
#include "shader/Shader.h"
/*
GL_ARRAY_BUFFER
The buffer will be used as a source for vertex data, but the connection is only made when glVertexAttribPointer is called. 
The pointer field of this function is taken as a byte offset from the beginning of whatever buffer is currently bound to this target.

GL_ELEMENT_ARRAY_BUFFER
All rendering functions of the form gl*Draw*Elements* will use the pointer field as a byte offset from the beginning of the buffer object bound to this target. 
The indices used for indexed rendering will be taken from the buffer object. Note that this binding target is part of a Vertex Array Objects state, so a VAO must be bound before binding a buffer here.

GL_COPY_READ_BUFFER 
GL_COPY_WRITE_BUFFER
These have no particular semantics. Because they have no actual meaning, they are useful targets for copying buffer object data with glCopyBufferSubData. 
You do not have to use these targets when copying, but by using them, you avoid disturbing buffer targets that have actual semantics.

GL_PIXEL_UNPACK_BUFFER
GL_PIXEL_PACK_BUFFER
These are for performing asynchronous pixel transfer operations. 
If a buffer is bound to GL_PIXEL_UNPACK_BUFFER, glTexImage*, glTexSubImage*, glCompressedTexImage*, and glCompressedTexSubImage* are all affected. 
These functions will read their data from the bound buffer object instead of where a client pointer points. 
Similarly, if a buffer is bound to GL_PIXEL_PACK_BUFFER, glGetTexImage, and glReadPixels will store their data to the bound buffer object instead of where a client pointer points.

GL_QUERY_BUFFER
These are for performing direct writes from asynchronous queries to buffer object memory. If a buffer is bound to GL_QUERY_BUFFER, then all glGetQueryObject[ui64v] 
function calls will write the result to an offset into the bound buffer object.

GL_TEXTURE_BUFFER
This target has no special semantics.

GL_TRANSFORM_FEEDBACK_BUFFER
An indexed buffer binding for buffers used in Transform Feedback operations.

GL_UNIFORM_BUFFER
An indexed buffer binding for buffers used as storage for uniform blocks.

GL_DRAW_INDIRECT_BUFFER
The buffer bound to this target will be used as the source for the indirect data when performing indirect rendering. This requires OpenGL 4.0 or ARB_draw_indirect.

GL_ATOMIC_COUNTER_BUFFER
An indexed buffer binding for buffers used as storage for atomic counters. This requires OpenGL 4.2 or ARB_shader_atomic_counters

GL_DISPATCH_INDIRECT_BUFFER
The buffer bound to this target will be used as the source for indirect compute dispatch operations, via glDispatchComputeIndirect. This requires OpenGL 4.3 or ARB_compute_shader.

GL_SHADER_STORAGE_BUFFER
An indexed buffer binding for buffers used as storage for shader storage blocks. This requires OpenGL 4.3 or ARB_shader_storage_buffer_objec
*/

namespace PROKARYOTIC
{

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
        Vertex(glm::vec3(0.5f,  0.5f, 0.0f),  glm::vec2(1.0f,1.0f), glm::vec3(1.0f, 0.0f, 0.0f)),
        Vertex(glm::vec3(0.5f, -0.5f, 0.0f),  glm::vec2(1.0f,0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
        Vertex(glm::vec3(-0.5f, -0.5f, 0.0f),  glm::vec2(0.0f,0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
        Vertex(glm::vec3(-0.5f,  0.5f, 0.0f),  glm::vec2(0.0f,1.0f), glm::vec3(1.0f, 1.0f, 0.0f))
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
}