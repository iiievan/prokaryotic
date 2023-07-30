#include "Texture.h"

#include <assert.h>
#include <string>

#include "stb\stb_image.h"

namespace PROKARYOTIC
{

    Texture_param_t::Texture_param_t(std::string  fname, bool srgb)
    {
        char* path = Get_texture_path(fname);
        int  nrComponents;

        switch (internal_format)
        {
        case GL_RGB:
            internal_format = (srgb ? GL_SRGB : GL_RGB);
            break;
        case GL_SRGB:
            internal_format = (srgb ? GL_SRGB : GL_RGB);
            break;
        case GL_SRGB_ALPHA:
            internal_format = (srgb ? GL_SRGB_ALPHA : GL_RGBA);
            break;
        case GL_RGBA:
            internal_format = (srgb ? GL_SRGB_ALPHA : GL_RGBA);
            break;
        default:
            break;
        }

        // flip textures on their y coordinate while loading
        stbi_set_flip_vertically_on_load(true);
        unsigned char* p_image_data = stbi_load(path, &width, &height, &nrComponents, 0);

        if (p_image_data)
        {
            switch (nrComponents)
            {
            case 1:
                format = GL_RED;
                break;
            case 3:
                format = GL_RGB;
                break;
            case 4:
                format = GL_RGBA;
                break;
            default:
                break;
            }
        }
        else
            printf("Texture failed to load at path: %s", path);

        stbi_image_free(p_image_data);
    }

    char* Texture_param_t::Get_texture_path(const std::string& fname)
    {
        TCHAR c_path[MAX_PATH];
        char* result = nullptr;

        GetModuleFileName(NULL, c_path, (sizeof(c_path)));  // get execution filepath

        PathRemoveFileSpec(c_path); // remove name of program from path

        // make shader filepath
        std::wstring wStr = c_path;
        std::string directory = std::string(wStr.begin(), wStr.end());
        directory = directory - "\\sandbox" - "\\Debug-windows-x86_64" - "\\bin";
        directory = directory + "\\resources" + "\\textures\\";
        directory = directory + fname;

        result = new char[directory.length() + 1];

        result[directory.length()] = '\0';  // make sure that the new string is null terminated

        memcpy(result, directory.c_str(), directory.length() + 1);

        return result;
    }

    Texture::Texture(GLenum  texture_type,      // type of texture: [ GL_TEXTURE_1D, GL_TEXTURE_2D ,GL_TEXTURE_3D, GL_TEXTURE_CUBE_MAP ]
            Texture_param_t  params)
    {
        m_texture_type = texture_type;
        glGenTextures(1, &m_ID);

        Bind();

        switch (m_texture_type)
        {
            case GL_TEXTURE_1D:
                glTexImage1D(m_texture_type, 0, params.internal_format, params.width, 0, 
                             params.format, params.pixel_datatype, params.p_image_data);
                glTexParameteri(m_texture_type, GL_TEXTURE_MIN_FILTER, params.filter_max);
                glTexParameteri(m_texture_type, GL_TEXTURE_MAG_FILTER, params.filter_min);
                glTexParameteri(m_texture_type, GL_TEXTURE_WRAP_S, params.wrap_S);
                break;
            case GL_TEXTURE_2D:
                glTexImage2D(m_texture_type, 0, params.internal_format, 
                             params.width, params.height, 0, 
                             params.format, params.pixel_datatype, params.p_image_data);
                glTexParameteri(m_texture_type, GL_TEXTURE_MIN_FILTER, params.filter_max);
                glTexParameteri(m_texture_type, GL_TEXTURE_MAG_FILTER, params.filter_min);
                glTexParameteri(m_texture_type, GL_TEXTURE_WRAP_S, params.wrap_S);
                glTexParameteri(m_texture_type, GL_TEXTURE_WRAP_T, params.wrap_T);
                break;
            case GL_TEXTURE_3D:
                glTexImage3D(m_texture_type, 0, params.internal_format, 
                            params.width, params.height, params.depth, 0, 
                            params.format, params.pixel_datatype, params.p_image_data);
                glTexParameteri(m_texture_type, GL_TEXTURE_MIN_FILTER, params.filter_max);
                glTexParameteri(m_texture_type, GL_TEXTURE_MAG_FILTER, params.filter_min);
                glTexParameteri(m_texture_type, GL_TEXTURE_WRAP_S, params.wrap_S);
                glTexParameteri(m_texture_type, GL_TEXTURE_WRAP_T, params.wrap_T);
                glTexParameteri(m_texture_type, GL_TEXTURE_WRAP_R, params.wrap_R);
                break;
            case GL_TEXTURE_CUBE_MAP:
                break;
            defalt:
                break;
        }

        if (params.mipmapping)
            glGenerateMipmap(m_texture_type);

        Unbind();        
    }

    char* Texture::m_Get_texture_path(const std::string& fname)
    {

    }

    void Texture::Generate(unsigned int width, GLenum internalFormat, GLenum format, GLenum type, void* data)
    {
        glGenTextures(1, &m_ID);

        m_Width = width;
        m_Height = 0;
        m_Depth = 0;
        m_Internal_format = internalFormat;
        m_Format = format;
        m_Type = type;

        //assert(m_Target == GL_TEXTURE_1D);
        Bind();

        glTexImage1D(m_Target, 0, internalFormat, width, 0, format, type, data);
        glTexParameteri(m_Target, GL_TEXTURE_MIN_FILTER, m_Filter_min);
        glTexParameteri(m_Target, GL_TEXTURE_MAG_FILTER, m_Filter_max);
        glTexParameteri(m_Target, GL_TEXTURE_WRAP_S, m_Wrap_S);

        if (m_Mipmapping)
            glGenerateMipmap(m_Target);

        Unbind();
    }

    void Texture::Generate(unsigned int width, unsigned int height, GLenum internalFormat, GLenum format, GLenum type, void* data)
    {
        glGenTextures(1, &m_ID);

        m_Width = width;
        m_Height = height;
        m_Depth = 0;
        m_Internal_format = internalFormat;
        m_Format = format;
        m_Type = type;

        //assert(m_Target == GL_TEXTURE_2D);
        Bind();

        glTexImage2D(m_Target, 0, internalFormat, width, height, 0, format, type, data);
        glTexParameteri(m_Target, GL_TEXTURE_MIN_FILTER, m_Filter_min);
        glTexParameteri(m_Target, GL_TEXTURE_MAG_FILTER, m_Filter_max);
        glTexParameteri(m_Target, GL_TEXTURE_WRAP_S, m_Wrap_S);
        glTexParameteri(m_Target, GL_TEXTURE_WRAP_T, m_Wrap_T);

        if (m_Mipmapping)
            glGenerateMipmap(m_Target);

        Unbind();
    }

    void Texture::Generate(unsigned int width, unsigned int height, unsigned int depth, GLenum internalFormat, GLenum format, GLenum type, void* data)
    {
        glGenTextures(1, &m_ID);

        m_Width = width;
        m_Height = height;
        m_Depth = depth;
        m_Internal_format = internalFormat;
        m_Format = format;
        m_Type = type;

        //assert(m_Target == GL_TEXTURE_3D);
        Bind();

        glTexImage3D(m_Target, 0, internalFormat, width, height, depth, 0, format, type, data);
        glTexParameteri(m_Target, GL_TEXTURE_MIN_FILTER, m_Filter_min);
        glTexParameteri(m_Target, GL_TEXTURE_MAG_FILTER, m_Filter_max);
        glTexParameteri(m_Target, GL_TEXTURE_WRAP_S, m_Wrap_S);
        glTexParameteri(m_Target, GL_TEXTURE_WRAP_T, m_Wrap_T);
        glTexParameteri(m_Target, GL_TEXTURE_WRAP_R, m_Wrap_R);

        if (m_Mipmapping)
            glGenerateMipmap(m_Target);

        Unbind();
    }

    void Texture::Resize(unsigned int width, unsigned int height, unsigned int depth)
    {
        Bind();

        if (m_Target == GL_TEXTURE_1D)
        {
            glTexImage1D(GL_TEXTURE_1D, 0, m_Internal_format, width, 0, m_Format, m_Type, 0);
        }
        else
        if (m_Target == GL_TEXTURE_2D)
        {
            assert(height > 0);
            glTexImage2D(GL_TEXTURE_2D, 0, m_Internal_format, width, height, 0, m_Format, m_Type, 0);
        }
        else
        if (m_Target == GL_TEXTURE_3D)
        {
            assert(height > 0 && depth > 0);
            glTexImage3D(GL_TEXTURE_3D, 0, m_Internal_format, width, height, depth, 0, m_Format, m_Type, 0);
        }
    }

    void Texture::Bind(int i)
    {
        // i - number of array of texture units ~ 8 arrays for simultaneously texture drawing;
        if (i >= 0)
            glActiveTexture(GL_TEXTURE0 + i);   // 0 and GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS.

        glBindTexture(m_texture_type, m_ID);
    }

    void Texture::Unbind()
    {
        glBindTexture(m_texture_type, 0);
    }

    void Texture::set_GL_Wrap_mode(GLenum wrapMode, bool bind)
    {
        if (bind)
            Bind();

        if (m_Target == GL_TEXTURE_1D)
        {
            m_Wrap_S = wrapMode;
            glTexParameteri(m_Target, GL_TEXTURE_WRAP_S, wrapMode);
        }
        else
        if (m_Target == GL_TEXTURE_2D)
        {
            m_Wrap_S = wrapMode;
            m_Wrap_T = wrapMode;
            glTexParameteri(m_Target, GL_TEXTURE_WRAP_S, wrapMode);
            glTexParameteri(m_Target, GL_TEXTURE_WRAP_T, wrapMode);
        }
        else
        if (m_Target == GL_TEXTURE_3D)
        {
            m_Wrap_S = wrapMode;
            m_Wrap_T = wrapMode;
            m_Wrap_R = wrapMode;
            glTexParameteri(m_Target, GL_TEXTURE_WRAP_S, wrapMode);
            glTexParameteri(m_Target, GL_TEXTURE_WRAP_T, wrapMode);
            glTexParameteri(m_Target, GL_TEXTURE_WRAP_R, wrapMode);
        }
    }

    void Texture::set_GL_Filter(GLenum filter_min, GLenum filter_max, bool bind)
    {
        if (bind)
            Bind();

        glTexParameteri(m_Target, GL_TEXTURE_MIN_FILTER, filter_min);
        glTexParameteri(m_Target, GL_TEXTURE_MAG_FILTER, filter_max);
    }
}
