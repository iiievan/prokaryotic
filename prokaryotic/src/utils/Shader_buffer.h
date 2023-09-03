#ifndef BUFFER_H_
#define BUFFER_H_

#include<GLAD/glad.h>

class Shader_buffer 
{
public:
    Shader_buffer(GLenum buffer_type, unsigned int data_size, GLvoid* data, GLenum memory_type)
    {
        m_buffer_type = buffer_type;
        glGenBuffers(1, &m_ID);
        glBindBuffer(m_buffer_type, m_ID);
        glBufferData(m_buffer_type, data_size, data, memory_type);
        glBindBuffer(m_buffer_type, 0);
    }

    void update(int offset, int size, GLvoid* data)
    {
        glBindBuffer(m_buffer_type, m_ID);
        glBufferSubData(m_buffer_type, offset, size, data);     // add support for map range instead of bufferSubData
        glBindBuffer(m_buffer_type, 0);
    }

    void bind()             { glBindBuffer(m_buffer_type, m_ID); }
    void bind_to(int base)  { glBindBufferBase(m_buffer_type, base, m_ID); }
    void unbind()           { glBindBuffer(m_buffer_type, 0); }

    ~Shader_buffer()        { glDeleteBuffers(1, &m_ID); }
private:
    GLuint m_ID;
    GLenum m_buffer_type;
};

#endif //Buffer.h