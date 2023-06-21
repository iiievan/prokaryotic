#include "utils/Frame_buffer.h"

Frame_buffer::Frame_buffer(int w, int h) 
{
    m_width = w;
    m_height = h;
}

Frame_buffer::Frame_buffer(int w, int h, GLuint texID) 
{
    m_width = w;
    m_height = h;
    glGenFramebuffers(1, &m_ID);
    glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texID, 0);

    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32F, w, h);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Frame_buffer::use() 
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
    glViewport(0, 0, m_width, m_height);
}

void Frame_buffer::clear_to_color(glm::vec4 col) 
{
    glClearColor(col.r, col.g, col.b, col.a); glClear(GL_COLOR_BUFFER_BIT);
}

void Frame_buffer::clear() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


