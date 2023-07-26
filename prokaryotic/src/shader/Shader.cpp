#include "Shader.h"

namespace PROKARYOTIC
{
    Shader::Shader(const GLchar* vertex_Path, const GLchar* frag_Path, const GLchar* geo_Path, bool debug) 
    {
          std::string  vertex_Code;
          std::string  frag_Code;
          std::string  geo_Code;
    
        if (geo_Path != nullptr)
            m_type = VFG;
        else
            m_type = VF;

        m_vCode = m_Get_shader_code(vertex_Path).c_str();       // read vertex file
        m_fCode = m_Get_shader_code(frag_Path).c_str();         // read fragment file

        if (geo_Path != nullptr) 
        {
            m_gCode = m_Get_shader_code(geo_Path).c_str();      // read geometry file
        }    

        if (debug)
        {
            std::cout << m_vCode << std::endl << std::endl;
            std::cout << m_fCode << std::endl << std::endl;
    
            if (geo_Path != nullptr)
                std::cout << m_fCode << std::endl << std::endl;
        }

        GLuint vertex, fragment, geometry;
         GLint success;
        GLchar info_log[512];

        //compile vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &m_vCode, NULL);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

        if (!success) 
        {
            glGetShaderInfoLog(vertex, 512, NULL, info_log);
            std::cout << "ERROR: Vertex shader COMPILATION_FAILED\n" << info_log << std::endl;
        }
        else 
        {
            std::cout << "Compiled Vertex Shader: " << vertex_Path << std::endl;
        }

        //compile fragment shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &m_fCode, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

        if (!success) 
        {
            glGetShaderInfoLog(fragment, 512, NULL, info_log);
            std::cout << "ERROR: Fragment shader COMPILATION_FAILED\n" << info_log << std::endl;
        }
        else 
        {
            std::cout << "Compiled Fragment Shader: " << frag_Path << std::endl;
        }

        if (geo_Path != nullptr)
        {
            //compile geometry shader
            geometry = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(geometry, 1, &m_gCode, NULL);
            glCompileShader(geometry);
            glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
    
            if (!success) 
            {
                glGetShaderInfoLog(geometry, 512, NULL, info_log);
                std::cout << "ERROR: Geometry shader COMPILATION_FAILED\n" << info_log << std::endl;
            }
            else 
            {
                std::cout << "Compiled Geometry Shader: " << geo_Path << std::endl;
            }
        }

        // link shaders to program
        m_ID = glCreateProgram();
        glAttachShader(m_ID, vertex);
        glAttachShader(m_ID, fragment);
    
        if (geo_Path != nullptr)
            glAttachShader(m_ID, geometry);
    
        glLinkProgram(m_ID);
        glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    
        if (!success)
        {
            glGetProgramInfoLog(m_ID, 512, NULL, info_log);
            std::cout << "ERROR: Shader program LINKING_FAILED\n" << info_log << std::endl;
        }

        //delete shaders
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        if (geo_Path != nullptr)
            glDeleteShader(fragment);
    }

    Shader::Shader(const std::string& GLSL_filename, e_GLSL_shader_type type)
    {
        char* path = m_Get_shader_path(GLSL_filename);

        m_Shader_source_code = m_Read_file(path);

        m_Shader_type = type;

        delete path;
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_ID);
    }

    bool Shader::compile(GLuint shader_ID)
    {
        GLint success;
        GLchar info_Log[512];

        //compile vertex shader
        shader_ID = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(shader_ID, 1, &m_vCode, NULL);
        glCompileShader(shader_ID);
        glGetShaderiv(shader_ID, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(shader_ID, 512, NULL, info_Log);
            std::cout << "ERROR: Vertex shader COMPILATION_FAILED\n" << info_Log << std::endl;
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
            glAttachShader(m_shader_program_ID, m_ID);
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

    int Shader::get_Uniform_location(const char* name) const
    {
        int result = glGetUniformLocation(m_ID, name);

        if (glGetError() != GL_NO_ERROR)
            printf("Shader ID:%d.Can't locate uniform (%s).\n", m_ID, name);

        return result;
    }

    void  Shader::set_Uniform(const std::string& name, float x, float y) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());

        if (glGetError() != GL_NO_ERROR)
            printf("Shader ID:%d.Error retrieving 2f uniform location (%s).\n", (int)m_ID, name.c_str());

        if (location >= 0)
            glUniform2f(location, x, y);
        else
            printf("Uniform(%s): %d not found.\n", name.c_str(), location);
    }

    void  Shader::set_Uniform(const std::string& name, float x, float y, float z) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());

        if (glGetError() != GL_NO_ERROR)
            printf("Shader ID:%d.Error retrieving 3f uniform location (%s).\n", (int)m_ID, name.c_str());

        if (location >= 0)
            glUniform3f(location, x, y, z);
        else
            printf("Uniform (%s) not found.Location(%d).", name.c_str(), location);
    }

    void  Shader::set_Uniform(const std::string& name, const glm::vec2& v) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());

        if (glGetError() != GL_NO_ERROR)
            printf("Shader ID:%d.Error retrieving v2 uniform location (%s).\n", (int)m_ID, name.c_str());

        if (location >= 0)
            glUniform2f(location, v.x, v.y);
        else
            printf("Uniform (%s) not found.Location(%d).", name.c_str(), location);
    }

    void  Shader::set_Uniform(const std::string& name, const glm::vec3& v) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());

        if (glGetError() != GL_NO_ERROR)
            printf("Shader ID:%d.Error retrieving v3 uniform location (%s).\n", (int)m_ID, name.c_str());

        if (location >= 0)
            glUniform3f(location, v.x, v.y, v.z);
        else
            printf("Uniform (%s) not found.Location(%d).", name.c_str(), location);
    }

    void  Shader::set_Uniform(const std::string& name, const glm::vec4& v) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());

        if (glGetError() != GL_NO_ERROR)
            printf("Shader ID:%d.Error retrieving vec4 uniform location (%s).\n", (int)m_ID, name.c_str());

        if (location >= 0)
            glUniform4f(location, v.x, v.y, v.z, v.w);
        else
            printf("Uniform (%s) not found.Location(%d).", name.c_str(), location);
    }

    void  Shader::set_Uniform(const std::string& name, const glm::mat2& m) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());

        if (glGetError() != GL_NO_ERROR)
            printf("Shader ID:%d.Error retrieving m2 uniform location (%s).\n", (int)m_ID, name.c_str());

        if (location >= 0)
            glUniformMatrix2fv(location, 1, GL_FALSE, &m[0][0]);
        else
            printf("Uniform (%s) not found.Location(%d).", name.c_str(), location);
    }

    void  Shader::set_Uniform(const std::string& name, const glm::mat3& m) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());

        if (glGetError() != GL_NO_ERROR)
            printf("Shader ID:%d.Error retrieving m4 uniform location (%s).\n", (int)m_ID, name.c_str());

        if (location >= 0)
            glUniformMatrix3fv(location, 1, GL_FALSE, &m[0][0]);
        else
            printf("Uniform (%s) not found.Location(%d).", name.c_str(), location);
    }

    void  Shader::set_Uniform(const std::string& name, const glm::mat4& m) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());
        
        if (glGetError() != GL_NO_ERROR)
            printf("Shader ID:%d.Error retrieving m4 uniform location (%s).\n", (int)m_ID, name.c_str());

        if (location >= 0)
            glUniformMatrix4fv(location, 1, GL_FALSE, &m[0][0]);
        else
            printf("Uniform (%s) not found.Location(%d).", name.c_str(), location);
    }

    void  Shader::set_Uniform(const std::string& name, float val) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());
        
        if (glGetError() != GL_NO_ERROR)
            printf("Shader ID:%d.Error retrieving float uniform location (%s).\n", (int)m_ID, name.c_str());

        if (location >= 0)
            glUniform1f(location, val);
        else
            printf("Uniform (%s) not found.Location(%d).", name.c_str(), location);
    }

    void  Shader::set_Uniform(const std::string& name, int val) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());
        
        if (glGetError() != GL_NO_ERROR)
            printf("Shader ID:%d.Error retrieving int uniform location (%s).\n", (int)m_ID, name.c_str());

        if (location >= 0)
            glUniform1i(location, val);
        else
            printf("Uniform (%s) not found.Location(%d).", name.c_str(), location);
    }

    void  Shader::set_Uniform(const std::string& name, bool val) const
    {
        int location = glGetUniformLocation(m_ID, name.c_str());

        if (glGetError() != GL_NO_ERROR)
            printf("Shader ID:%d.Error retrieving bool uniform location (%s).\n", (int)m_ID, name.c_str());

        if (location >= 0)
            glUniform1i(location, val);
        else
            printf("Uniform (%s) not found.Location(%d).", name.c_str(), location);
    }

    void Shader::print_Active_uniforms()
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

    void Shader::print_Active_attribs()
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

    std::string  Shader::m_Get_shader_code(const GLchar* file_Path)
    {
        std::string sh_code;
        std::ifstream sh_File;

        //read vertex file
        sh_File.open(file_Path);

        if (sh_File.is_open())
        {
            std::stringstream s_Stream;

            s_Stream << sh_File.rdbuf();
            sh_code = s_Stream.str();
        }
        else
        {
            std::cout << "ERROR: Can't open vertex shader file at: " << file_Path << std::endl;
        }

        sh_File.close();

        return sh_code;
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