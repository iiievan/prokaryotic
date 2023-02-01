#include "Mesh.h"

// GL_ARRAY_BUFFER              - The buffer will be used as a source for vertex data
// GL_ELEMENT_ARRAY_BUFFER
// GL_COPY_READ_BUFFER 
// GL_COPY_WRITE_BUFFER
// GL_PIXEL_UNPACK_BUFFER
// GL_PIXEL_PACK_BUFFER
// GL_QUERY_BUFFER
// GL_TEXTURE_BUFFER
// GL_TRANSFORM_FEEDBACK_BUFFER
// GL_UNIFORM_BUFFER
// GL_DRAW_INDIRECT_BUFFER
// GL_ATOMIC_COUNTER_BUFFER
// GL_DISPATCH_INDIRECT_BUFFER
// GL_DISPATCH_INDIRECT_BUFFER
// GL_SHADER_STORAGE_BUFFER

float mesh_vertices[] =
{
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

Mesh::Mesh(float *vertices)
: m_Vertices(vertices) 
{
    glGenBuffers(1, &m_VBO_ID);                  // generate VBO buffer on GPU    
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO_ID);     // set type of buffer

    glGenVertexArrays(1, &m_VAO_ID);             // generate vertex array buffer for VBO
    glBindVertexArray(m_VAO_ID); 
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_VAO_ID);
    glDeleteBuffers(1, &m_VBO_ID);
}

void  Mesh::load_to_GPU(size_t vertices_num)
{
    // fill buffer with vertices
    glBufferData(GL_ARRAY_BUFFER,           
                 sizeof(float)*3*vertices_num,  // size of vertices is 3 float numbers
                 m_Vertices,
                 GL_STATIC_DRAW);

    //GL_STREAM_DRAW: данные устанавливаются только один раз и используются графическим процессором не более нескольких раз.
    //GL_STATIC_DRAW : данные устанавливаются только один раз и используются многократно.
    //GL_DYNAMIC_DRAW : данные сильно изменяются и используются многократно.

    // set how to read vertices and enable VAO use
    glVertexAttribPointer(0, vertices_num, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); 
    glEnableVertexAttribArray(0);
}

void  Mesh::draw()
{
    glBindVertexArray(m_VAO_ID);
    glDrawArrays(GL_TRIANGLES, 0, 3);   // 3. now draw the object
}