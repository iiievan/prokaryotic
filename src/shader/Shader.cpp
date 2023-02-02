#include "Shader.h"

Shader::Shader(const std::string & GLSL_filename, GLuint type)
{
    char *path = get_shader_path(GLSL_filename);

    m_Shader_source_code = Read_file(path);

    m_Shader_type = type;

    delete path;
}

Shader::~Shader() 
{ 
    glDeleteShader(m_Shader_glID); 
}

void Shader::compile()
{
    int  success;
    GLchar* p_shader_src = new GLchar[m_Shader_source_code.length() + 1];

    memcpy(p_shader_src, m_Shader_source_code.c_str(), m_Shader_source_code.length() + 1);

    GLchar** shader_code = new GLchar * [1];

    *shader_code = p_shader_src;

    m_Shader_glID = glCreateShader(m_Shader_type);

    glShaderSource(m_Shader_glID, 1, reinterpret_cast<const GLchar * const *>(shader_code), NULL);
    glCompileShader(m_Shader_glID);

    glGetShaderiv(m_Shader_glID, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(m_Shader_glID, 512, NULL, m_info_log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << m_info_log << std::endl;
    }

    delete [] p_shader_src;
    delete [] shader_code;
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
