#include "Shader.h"

Shader::Shader(const std::string & GLSL_filename, e_GLSL_shader_type type)
{
    char *path = get_shader_path(GLSL_filename);

    m_Shader_source_code = Read_file(path);

    m_Shader_type = type;

    delete path;
}

Shader::~Shader() 
{ 
    glDeleteShader(m_shader_ID);
    glDeleteProgram(m_shader_program_ID);
}

void Shader::print_log()
{
   if(m_info_log.length() > 0)
    {
        std::cout << m_info_log.c_str() << std::endl;
        m_info_log = "";
    }
}

bool Shader::compile()
{
    //Create the program if we havn't already got one
    if (m_shader_program_ID <= 0)
    {
        m_shader_program_ID = glCreateProgram();

        if (m_shader_program_ID == 0)
        {
            m_info_log = "Loading Shader: Unable to create shader program.";
            print_log();
            return false;
        }
    }

    //set up the specific shader part
    switch (m_Shader_type)
    {
    case VERTEX:
        m_shader_ID = glCreateShader(GL_VERTEX_SHADER);
        break;
    case FRAGMENT:
        m_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);
        break;
    case GEOMETRY:
        m_shader_ID = glCreateShader(GL_GEOMETRY_SHADER);
        break;
    default:
        m_info_log = "Loading Shader: Unrecognised shader type.";
        print_log();
        return false;
    }

    //load and compile the shader
    const char* c_code = m_Shader_source_code.c_str();

    glShaderSource(m_shader_ID, 1, &c_code, NULL);
    glCompileShader(m_shader_ID);

    //check for errors
    int result;
    glGetShaderiv(m_shader_ID, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        //compile failed, log the error and return false
        int length = 0;
        m_info_log = "";
        glGetShaderiv(m_shader_ID, GL_INFO_LOG_LENGTH, &length);
        if(length)
        {
            char* c_log = new char[length];
            int written = 0;
            glGetShaderInfoLog(m_shader_ID, length, &written, c_log);
            m_info_log = c_log;
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << std::endl;
            print_log();
            delete[] c_log;
        }
        return false;
    }
    else
    {
        //compile succeeded, attach shader and return true
        glAttachShader(m_shader_program_ID, m_shader_ID);
        return true;        
    }
}

bool Shader::link()
{
    if (!m_Linked)
    {
        if (m_shader_program_ID <= 0)
        {
            m_info_log = "Loading Shader: Linking failed. No shader handle ID.";
            print_log();
            return false;
        }

        glLinkProgram(m_shader_program_ID);
        //check that everything went well, if not, log an error and return false;
        int status = 0;
        glGetProgramiv(m_shader_program_ID, GL_LINK_STATUS, &status);
        if (!status)
        {
            int length = 0;
            m_info_log = "";
            glGetProgramiv(m_shader_program_ID, GL_INFO_LOG_LENGTH, &length);
            if (length > 0)
            {
                char* c_log = new char[length];
                int written = 0;
                glGetProgramInfoLog(m_shader_program_ID, length, &written, c_log);
                m_info_log = c_log;
                print_log();
                delete[] c_log;
            }
        }
        m_Linked = true;
    }

    //everything succeeded, return m_Linked (should be true)
    return m_Linked;
}

bool Shader::validate()
{
    if (!m_Linked)
    {
        m_info_log = "Loading Shader: Validation failed, shader is not m_Linked.";
        print_log();
        return false;
    }
    int status;
    glValidateProgram(m_shader_program_ID);
    glGetProgramiv(m_shader_program_ID, GL_VALIDATE_STATUS, &status);
    
    //validation failed, log it and return false
    if (!status)
    {
        int length = 0;
        m_info_log = "";
        glGetProgramiv(m_shader_program_ID, GL_INFO_LOG_LENGTH, &length);
        if (length > 0)
        {
            char * c_log = new char[length];
            int written = 0;
            glGetProgramInfoLog(m_shader_program_ID, length, &written, c_log);
            m_info_log = c_log;
            delete[] c_log;
        }
        else
        {
            m_info_log = "Shader validation failed, but OpenGL has nothing to say about why.\n";
        }
        print_log();
        return false;
    }
    else
    {
        //validation passed, return true
        m_Validated = true;  
    }

    return m_Validated;
}

bool Shader::link_and_validate()
{
    if (!link())
    {
        return false;
    }

    if (!validate())
    {
        return false;
    }

    return true;
}

void Shader::use()
{
    if (m_shader_program_ID > 0 &&
        m_Linked)
    {
        glUseProgram(m_shader_program_ID);
    }
}

void Shader::bind_Attrib_location(GLuint location, const char* name)
{
    glBindAttribLocation(m_shader_program_ID, location, name);
}

void Shader::bind_Frag_data_location(GLuint location, const char* name)
{
    glBindFragDataLocation(m_shader_program_ID, location, name);
}

int Shader::get_Uniform_location(const char* name)
{
    int result = glGetUniformLocation(m_shader_program_ID, name);
    if (glGetError() != GL_NO_ERROR)
    {
        printf("Error occured retrieving uniform location: ");
        printf(name);
        printf("\n");
    }
    return result;
}

void Shader::set_Uniform(GLint location, float x, float y)
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

void Shader::set_Uniform(GLint location, float x, float y, float z)
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

void Shader::set_Uniform(GLint location, const glm::vec2& v)
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

void Shader::set_Uniform(GLint location, const glm::vec3& v)
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

void Shader::set_Uniform(GLint location, const glm::vec4& v)
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

void Shader::set_Uniform(GLint location, const glm::mat4& m)
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

void Shader::set_Uniform(GLint location, const glm::mat3& m)
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

void Shader::set_Uniform(GLint location, float val)
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

void Shader::set_Uniform(GLint location, int val)
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

void Shader::set_Uniform(GLint location, bool val)
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

void Shader::print_Active_uniforms()
{
    GLint numUniforms, size, location, maxLength;
    GLchar* name;
    GLsizei written;
    GLenum type;

    glGetProgramiv(m_shader_program_ID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);
    glGetProgramiv(m_shader_program_ID, GL_ACTIVE_UNIFORMS, &numUniforms);

    //allocate memory for the uniform name
    name = (GLchar*)malloc(maxLength);
    printf(" Location | Name\n");
    printf("------------------------------------------------\n");
    
    for (int i = 0; i < numUniforms; i++)
    {
        glGetActiveUniform(m_shader_program_ID, i, maxLength, &written, &size, &type, name);
        location = glGetUniformLocation(m_shader_program_ID, name);
        printf(" %-8d | %s\n", location, name);
    }
    //free memory allocated for the uniform name
    free(name);
}

void Shader::print_Active_attribs()
{
    GLint written, size, location, maxLength, numAttribs;
    GLenum type;
    GLchar* name;

    glGetProgramiv(m_shader_program_ID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);
    glGetProgramiv(m_shader_program_ID, GL_ACTIVE_ATTRIBUTES, &numAttribs);
    //allocate memory for the attribute name
    name = (GLchar*)malloc(maxLength);
    printf(" Index | Name\n");
    printf("------------------------------------------------\n");
    for (int i = 0; i < numAttribs; i++)
    {
        glGetActiveAttrib(m_shader_program_ID, i, maxLength, &written, &size, &type, name);
        location = glGetAttribLocation(m_shader_program_ID, name);
        printf(" %-5d | %s\n", location, name);
    }
    //free memory allocated for the attribute name
    free(name);
}

static std::string operator-(std::string source, const std::string& target)
{
    for (size_t pos, size{ target.size() }; (pos = source.find(target)) != std::string::npos; )
    {
        source.erase(source.cbegin() + pos,
        source.cbegin() + (pos + size));
    }

    return source;
}

char* get_shader_path(const std::string& sh_filename)
{
    TCHAR c_path[MAX_PATH];
    char* result = nullptr;

    GetModuleFileName(NULL, c_path, (sizeof(c_path)));  // get execution filepath

    PathRemoveFileSpec(c_path); // remove name of program from path

    // make shader filepath
    std::string directory = std::string(c_path);
    directory = directory - "\\Debug" - "\\x64";
    directory = directory + "\\shaders\\";
    directory = directory + sh_filename;

    result = new char[directory.length() + 1];

    result[directory.length()] = '\0';  // make sure that the new string is null terminated

    memcpy(result,directory.c_str(), directory.length() + 1);

    return result;
}


std::string Read_file(const char* filePath)
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
