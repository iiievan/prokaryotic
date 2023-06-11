#include "shader/Shader_program.h"

namespace PROKARYOTIC
{

    Shader_program::Shader_program()
    {
        m_ID = glCreateProgram();
    }

    Shader_program::~Shader_program()
    {
        glDeleteProgram(m_ID);
    }

    void Shader_program::load_shader(Shader* p_Sh)
    {
        m_Shaders_collection.push_back(p_Sh);

        p_Sh->compile(m_ID);
        p_Sh->link_and_validate(m_ID);
    }

    void Shader_program::use()
    {
        if (m_ID > 0)
        {
            glUseProgram(m_ID);
        }
    }

    void Shader_program::bind_Attrib_location(GLuint location, const char* name)
    {
        glBindAttribLocation(m_ID, location, name);
    }

    void Shader_program::bind_Frag_data_location(GLuint location, const char* name)
    {
        glBindFragDataLocation(m_ID, location, name);
    }

    int Shader_program::get_Uniform_location(const char* name) const
    {
        int result = glGetUniformLocation(m_ID, name);
        if (glGetError() != GL_NO_ERROR)
        {
            printf("Error occured retrieving uniform location: ");
            printf(name);
            printf("\n");
        }
        return result;
    }

    void Shader_program::set_Uniform(GLint location, float x, float y) const
    {
        if (location >= 0)
        {
            glUniform2f(location, x, y);
        }
        else
        {
            printf("Uniform: %d not found.\n", location);
        }
    }

    void Shader_program::set_Uniform(GLint location, float x, float y, float z) const
    {
        if (location >= 0)
        {
            glUniform3f(location, x, y, z);
        }
        else
        {
            printf("Uniform: %d not found.\n", location);
        }
    }

    void Shader_program::set_Uniform(GLint location, const glm::vec2& v) const
    {
        if (location >= 0)
        {
            glUniform2f(location, v.x, v.y);
        }
        else
        {
            printf("Uniform: %d not found.\n", location);
        }
    }

    void Shader_program::set_Uniform(GLint location, const glm::vec3& v) const
    {
        if (location >= 0)
        {
            glUniform3f(location, v.x, v.y, v.z);
        }
        else
        {
            printf("Uniform: %d not found.\n", location);
        }
    }

    void Shader_program::set_Uniform(GLint location, const glm::vec4& v) const
    {
        if (location >= 0)
        {
            glUniform4f(location, v.x, v.y, v.z, v.w);
        }
        else
        {
            printf("Uniform: %d not found.\n", location);
        }
    }

    void Shader_program::set_Uniform(GLint location, const glm::mat2& m) const
    {
        if (location >= 0)
        {
            glUniformMatrix2fv(location, 1, GL_FALSE, &m[0][0]);
        }
        else
        {
            printf("Uniform: %d not found.\n", location);
        }
    }

    void Shader_program::set_Uniform(GLint location, const glm::mat3& m) const
    {
        if (location >= 0)
        {
            glUniformMatrix3fv(location, 1, GL_FALSE, &m[0][0]);
        }
        else
        {
            printf("Uniform: %d not found.\n", location);
        }
    }

    void Shader_program::set_Uniform(GLint location, const glm::mat4& m) const
    {
        if (location >= 0)
        {
            glUniformMatrix4fv(location, 1, GL_FALSE, &m[0][0]);
        }
        else
        {
            printf("Uniform: %d not found.\n", location);
        }
    }

    void Shader_program::set_Uniform(GLint location, float val) const
    {
        if (location >= 0)
        {
            glUniform1f(location, val);
        }
        else
        {
            printf("Uniform: %d not found.\n", location);
        }
    }

    void Shader_program::set_Uniform(GLint location, int val) const
    {
        if (location >= 0)
        {
            glUniform1i(location, val);
        }
        else
        {
            printf("Uniform: %d not found.\n", location);
        }
    }

    void Shader_program::set_Uniform(GLint location, bool val) const
    {
        if (location >= 0)
        {
            glUniform1i(location, val);
        }
        else
        {
            printf("Uniform: %d not found.\n", location);
        }
    }

    void  Shader_program::set_Uniform(const std::string& name, float x, float y) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());
        if (glGetError() != GL_NO_ERROR)
        {
            printf("Error occured retrieving uniform location: ");
            printf(name.c_str());
            printf("\n");
        }

        if (location >= 0)
        {
            glUniform2f(location, x, y);
        }
        else
        {
            printf("Uniform: %d not found.\n", location);
        }
    }

    void  Shader_program::set_Uniform(const std::string& name, float x, float y, float z) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());
        if (glGetError() != GL_NO_ERROR)
        {
            printf("Error occured retrieving uniform location: ");
            printf(name.c_str());
            printf("\n");
        }

        if (location >= 0)
        {
            glUniform3f(location, x, y, z);
        }
        else
        {
            printf("Uniform: %d not found.\n", location);
        }
    }

    void  Shader_program::set_Uniform(const std::string& name, const glm::vec2& v) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());
        if (glGetError() != GL_NO_ERROR)
        {
            printf("Error occured retrieving uniform location: ");
            printf(name.c_str());
            printf("\n");
        }

        if (location >= 0)
        {
            glUniform2f(location, v.x, v.y);
        }
        else
        {
            printf("Uniform: %d not found.\n", location);
        }
    }

    void  Shader_program::set_Uniform(const std::string& name, const glm::vec3& v) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());

        if (glGetError() != GL_NO_ERROR)
        {
            printf("Error occured retrieving uniform location: ");
            printf(name.c_str());
            printf("\n");
        }

        if (location >= 0)
        {
            glUniform3f(location, v.x, v.y, v.z);
        }
        else
        {
            printf("Uniform: %d not found.\n", location);
        }
    }

    void  Shader_program::set_Uniform(const std::string& name, const glm::vec4& v) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());
        if (glGetError() != GL_NO_ERROR)
        {
            printf("Error occured retrieving uniform location: ");
            printf(name.c_str());
            printf("\n");
        }

        if (location >= 0)
        {
            glUniform4f(location, v.x, v.y, v.z, v.w);
        }
        else
        {
            printf("Uniform: %d not found.\n", location);
        }
    }

    void  Shader_program::set_Uniform(const std::string& name, const glm::mat2& m) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());
        if (glGetError() != GL_NO_ERROR)
        {
            printf("Error occured retrieving uniform location: ");
            printf(name.c_str());
            printf("\n");
        }

        if (location >= 0)
        {
            glUniformMatrix2fv(location, 1, GL_FALSE, &m[0][0]);
        }
        else
        {
            printf("Uniform: %d not found.\n", location);
        }
    }

    void  Shader_program::set_Uniform(const std::string& name, const glm::mat3& m) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());
        if (glGetError() != GL_NO_ERROR)
        {
            printf("Error occured retrieving uniform location: ");
            printf(name.c_str());
            printf("\n");
        }

        if (location >= 0)
        {
            glUniformMatrix3fv(location, 1, GL_FALSE, &m[0][0]);
        }
        else
        {
            printf("Uniform: %d not found.\n", location);
        }
    }

    void  Shader_program::set_Uniform(const std::string& name, const glm::mat4& m) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());
        if (glGetError() != GL_NO_ERROR)
        {
            printf("Error occured retrieving uniform location: ");
            printf(name.c_str());
            printf("\n");
        }

        if (location >= 0)
        {
            glUniformMatrix4fv(location, 1, GL_FALSE, &m[0][0]);
        }
        else
        {
            printf("Uniform: %d not found.\n", location);
        }
    }

    void  Shader_program::set_Uniform(const std::string& name, float val) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());
        if (glGetError() != GL_NO_ERROR)
        {
            printf("Error occured retrieving uniform location: ");
            printf(name.c_str());
            printf("\n");
        }

        if (location >= 0)
        {
            glUniform1f(location, val);
        }
        else
        {
            printf("Uniform: %d not found.\n", location);
        }
    }

    void  Shader_program::set_Uniform(const std::string& name, int val) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());
        if (glGetError() != GL_NO_ERROR)
        {
            printf("Error occured retrieving uniform location: ");
            printf(name.c_str());
            printf("\n");
        }

        if (location >= 0)
        {
            glUniform1i(location, val);
        }
        else
        {
            printf("Uniform: %d not found.\n", location);
        }
    }

    void  Shader_program::set_Uniform(const std::string& name, bool val) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());
        if (glGetError() != GL_NO_ERROR)
        {
            printf("Error occured retrieving uniform location: ");
            printf(name.c_str());
            printf("\n");
        }

        if (location >= 0)
        {
            glUniform1i(location, val);
        }
        else
        {
            printf("Uniform: %d not found.\n", location);
        }
    }

    void Shader_program::print_Active_uniforms()
    {
        GLint numUniforms, size, location, maxLength;
        GLsizei written;
        GLenum type;

        glGetProgramiv(m_ID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);
        glGetProgramiv(m_ID, GL_ACTIVE_UNIFORMS, &numUniforms);

        //allocate memory for the uniform name
        GLchar* name = new GLchar[maxLength];

        printf(" Location | Name\n");
        printf("------------------------------------------------\n");

        for (int i = 0; i < numUniforms; i++)
        {
            glGetActiveUniform(m_ID, i, maxLength, &written, &size, &type, name);
            location = glGetUniformLocation(m_ID, name);
            printf(" %-8d | %s\n", location, name);
        }

        delete[] name;
    }

    void Shader_program::print_Active_attribs()
    {
        GLint written, size, location, maxLength, numAttribs;
        GLenum type;

        glGetProgramiv(m_ID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);
        glGetProgramiv(m_ID, GL_ACTIVE_ATTRIBUTES, &numAttribs);

        //allocate memory for the attribute name
        GLchar* name = new GLchar[maxLength];

        printf(" Index | Name\n");
        printf("------------------------------------------------\n");
        for (int i = 0; i < numAttribs; i++)
        {
            glGetActiveAttrib(m_ID, i, maxLength, &written, &size, &type, name);
            location = glGetAttribLocation(m_ID, name);
            printf(" %-5d | %s\n", location, name);
        }

        delete[] name;
    }
}