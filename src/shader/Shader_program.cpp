#include "shader/Shader_program.h"

Shader_program::Shader_program()
{
    m_gl_ID = glCreateProgram();
}

Shader_program::~Shader_program()
{
    glDeleteProgram(m_gl_ID);
}

void Shader_program::load_shader(Shader* p_Sh)
{
    glAttachShader(m_gl_ID, p_Sh->get_shader_ID());

    m_Shaders_collection.push_back(p_Sh);
}

int Shader_program::link_program()
{
    int  success;

    if (m_Shaders_collection.empty())
        return -1;

    // firstly compile all shaders
    for (auto shader : m_Shaders_collection)
    {
        shader->compile();
    }

    // then link the program to GPU
    glLinkProgram(m_gl_ID);

    glGetProgramiv(m_gl_ID, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(m_gl_ID, 512, NULL, m_info_log);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << m_info_log << std::endl;
    }
    else
    {
        //m_Shaders_collection.clear();
    }

    return success;
}

void Shader_program::use()
{
    glUseProgram(m_gl_ID);
}