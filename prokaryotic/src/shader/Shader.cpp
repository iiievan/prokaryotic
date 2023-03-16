#include "Shader.h"

namespace PROKARYOTIC
{

    Shader::Shader(const std::string& GLSL_filename, e_GLSL_shader_type type)
    {
        char* path = m_Get_shader_path(GLSL_filename);

        m_Shader_source_code = m_Read_file(path);

        m_Shader_type = type;

        delete path;
    }

    Shader::~Shader()
    {
        glDeleteShader(m_ID);
        glDeleteProgram(m_shader_program_ID);
    }

    bool Shader::compile(GLuint shader_program_ID)
    {
        //Create the program if we havn't already got one
        if (shader_program_ID <= 0)
        {
            printf("Compile Shader: Unable to compile. No shader program handle ID.\n");
            return false;
        }
        else
        {
            if (m_shader_program_ID == 0)
                m_shader_program_ID = shader_program_ID;
        }

        //set up the specific shader part
        switch (m_Shader_type)
        {
        case VERTEX:
            m_ID = glCreateShader(GL_VERTEX_SHADER);
            break;
        case FRAGMENT:
            m_ID = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        case GEOMETRY:
            m_ID = glCreateShader(GL_GEOMETRY_SHADER);
            break;
        default:
            printf("Loading Shader: Unrecognised shader type.\n");
            return false;
        }

        //load and compile the shader
        const char* c_code = m_Shader_source_code.c_str();

        glShaderSource(m_ID, 1, &c_code, NULL);
        glCompileShader(m_ID);

        //check for errors
        int result;
        glGetShaderiv(m_ID, GL_COMPILE_STATUS, &result);
        if (!result)
        {
            //compile failed, log the error and return false
            int length = 0;
            glGetShaderiv(m_ID, GL_INFO_LOG_LENGTH, &length);
            if (length)
            {
                char* c_log = new char[length];
                int written = 0;
                glGetShaderInfoLog(m_ID, length, &written, c_log);
                printf("ERROR::SHADER::COMPILATION_FAILED\n");
                printf(c_log);
                delete[] c_log;
            }
            return false;
        }
        else
        {
            //compile succeeded, attach shader and return true
            glAttachShader(shader_program_ID, m_ID);
            return true;
        }
    }

    bool Shader::link(GLuint shader_program_ID)
    {
        if (!this->linked)
        {
            if (shader_program_ID <= 0)
            {
                printf("Loading Shader: Linking failed. No shader handle ID.\n");
                return false;
            }

            glLinkProgram(shader_program_ID);
            //check that everything went well, if not, log an error and return false;
            int status = 0;
            glGetProgramiv(shader_program_ID, GL_LINK_STATUS, &status);
            if (!status)
            {
                int length = 0;
                glGetProgramiv(shader_program_ID, GL_INFO_LOG_LENGTH, &length);
                if (length > 0)
                {
                    char* c_log = new char[length];
                    int written = 0;
                    glGetProgramInfoLog(shader_program_ID, length, &written, c_log);
                    printf("ERROR::SHADER::LINK_FAILED\n");
                    printf(c_log);
                    delete[] c_log;
                }
            }
            this->linked = true;
        }

        //everything succeeded, return linked (should be true)
        return this->linked;
    }

    bool Shader::validate(GLuint shader_program_ID)
    {
        if (!this->linked)
        {
            printf("Loading Shader: Validation failed, shader is not linked.\n");
            return false;
        }

        int status;
        glValidateProgram(shader_program_ID);
        glGetProgramiv(shader_program_ID, GL_VALIDATE_STATUS, &status);

        //validation failed, log it and return false
        if (!status)
        {
            int length = 0;
            glGetProgramiv(shader_program_ID, GL_INFO_LOG_LENGTH, &length);
            if (length > 0)
            {
                char* c_log = new char[length];
                int written = 0;
                glGetProgramInfoLog(shader_program_ID, length, &written, c_log);
                printf("ERROR::SHADER::VALIDATION_FAILED\n");
                printf(c_log);
                delete[] c_log;
            }
            else
            {
                printf("Shader validation failed, but OpenGL has nothing to say about why.\n");
            }

            return false;
        }
        else
        {
            //validation passed, return true
            this->validated = true;
        }

        return this->validated;
    }

    bool Shader::link_and_validate(GLuint shader_program_ID)
    {
        if (!link(shader_program_ID))
        {
            return false;
        }

        if (!validate(shader_program_ID))
        {
            return false;
        }

        return true;
    }

    char* Shader::m_Get_shader_path(const std::string& sh_filename)
    {
        TCHAR c_path[MAX_PATH];
        char* result = nullptr;

        GetModuleFileName(NULL, c_path, (sizeof(c_path)));  // get execution filepath

        PathRemoveFileSpec(c_path); // remove name of program from path

        // make shader filepath
        std::wstring wStr = c_path;
        std::string directory = std::string(wStr.begin(), wStr.end());
        directory = directory - "\\sandbox" - "\\Debug-windows-x86_64" - "\\bin";
        directory = directory + "\\shaders\\";
        directory = directory + sh_filename;

        result = new char[directory.length() + 1];

        result[directory.length()] = '\0';  // make sure that the new string is null terminated

        memcpy(result, directory.c_str(), directory.length() + 1);

        return result;
    }

    std::string Shader::m_Read_file(const char* filePath)
    {
        std::string content;
        std::ifstream fileStream(filePath);

        if (!fileStream.is_open())
        {
            std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
            return "";
        }

        std::string line = "";

        while (!fileStream.eof())
        {
            std::getline(fileStream, line);
            content.append(line + "\n");
        }

        fileStream.close();
        return content;
    }
}