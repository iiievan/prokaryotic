#include "Texture.h"

#include <assert.h>
#include <string>

namespace PROKARYOTIC
{    
    Texture::Texture(GLenum textype, std::string  fname, GLenum intform, bool mipmap, bool srgb)
    {
        char* path = m_Get_texture_path(fname);
         int  nrComponents;

         m_texture_type = textype;
         m_mipmapping = mipmap;

        switch (intform)
        {
            case GL_RGB:
                m_internal_format = (srgb ? GL_SRGB : GL_RGB);
                break;
            case GL_SRGB:
                m_internal_format = (srgb ? GL_SRGB : GL_RGB);
                break;
            case GL_SRGB_ALPHA:
                m_internal_format = (srgb ? GL_SRGB_ALPHA : GL_RGBA);
                break;
            case GL_RGBA:
                m_internal_format = (srgb ? GL_SRGB_ALPHA : GL_RGBA);
                break;
            default:
                break;
        }

        // flip textures on their y coordinate while loading
        stbi_set_flip_vertically_on_load(true);
        unsigned char*  p_image_data = stbi_load(path, &m_width, &m_height, &nrComponents, 0);

        if (p_image_data)
        {
            switch (nrComponents)
            {
            case 1:
                m_format = GL_RED;
                break;
            case 3:
                m_format = GL_RGB;
                break;
            case 4:
                m_format = GL_RGBA;
                break;
            default:
                break;
            }
        }
        else
            printf("Texture failed to load at path:%s.", path);         

        switch (m_texture_type)
        {
            case GL_TEXTURE_1D:
                set_wrap<GL_TEXTURE_1D>(GL_REPEAT);
                break;
            case GL_TEXTURE_2D:
                set_wrap<GL_TEXTURE_2D>(GL_REPEAT, GL_REPEAT);
                break;
            case GL_TEXTURE_3D:
                set_wrap<GL_TEXTURE_3D>(GL_REPEAT, GL_REPEAT, GL_REPEAT);
                break;
            case GL_TEXTURE_CUBE_MAP:
                //set_wrap<GL_TEXTURE_CUBE_MAP>();
                break;
            default:
                break;
        }
        GLuint ID;
        glGenTextures(1, &ID);

        m_ID = ID;

        Bind();

        if (p_image_data)
        {
            switch (m_texture_type)
            {
                case GL_TEXTURE_1D:
                    glTexImage1D(m_texture_type, 0, m_internal_format, m_width, 0,
                                 m_format, m_pixel_datatype, p_image_data);
                    glTexParameteri(m_texture_type, GL_TEXTURE_MIN_FILTER, m_filter_max);
                    glTexParameteri(m_texture_type, GL_TEXTURE_MAG_FILTER, m_filter_min);
                    glTexParameteri(m_texture_type, GL_TEXTURE_WRAP_S, m_wrap_S);
                    break;
                case GL_TEXTURE_2D:
                    glTexImage2D(m_texture_type, 0, m_internal_format,
                                 m_width, m_height, 0,
                                 m_format, m_pixel_datatype, p_image_data);
                    glTexParameteri(m_texture_type, GL_TEXTURE_MIN_FILTER, m_filter_max);
                    glTexParameteri(m_texture_type, GL_TEXTURE_MAG_FILTER, m_filter_min);
                    glTexParameteri(m_texture_type, GL_TEXTURE_WRAP_S, m_wrap_S);
                    glTexParameteri(m_texture_type, GL_TEXTURE_WRAP_T, m_wrap_T);
                    break;
                case GL_TEXTURE_3D:
                    glTexImage3D(m_texture_type, 0, m_internal_format,
                                 m_width, m_height, m_depth, 0,
                                 m_format, m_pixel_datatype, m_p_image_data);
                    glTexParameteri(m_texture_type, GL_TEXTURE_MIN_FILTER, m_filter_max);
                    glTexParameteri(m_texture_type, GL_TEXTURE_MAG_FILTER, m_filter_min);
                    glTexParameteri(m_texture_type, GL_TEXTURE_WRAP_S, m_wrap_S);
                    glTexParameteri(m_texture_type, GL_TEXTURE_WRAP_T, m_wrap_T);
                    glTexParameteri(m_texture_type, GL_TEXTURE_WRAP_R, m_wrap_R);
                    break;
                case GL_TEXTURE_CUBE_MAP:
                    break;
                default:
                    break;
            }

            if (m_mipmapping)
                glGenerateMipmap(m_texture_type);            
        }
        else
            printf("Texture failed to generate at ID:%d.", m_ID);

        stbi_image_free(p_image_data);

        Unbind();        
    }    

    void Texture::Bind(int i)
    {
        // i - number of array of texture units ~ mminimum 16 arrays for simultaneously texture drawing for one shader;
        if (i >= 0)
            glActiveTexture(GL_TEXTURE0 + i);   // from GL_TEXTURE0  to GL_TEXTURE15.

        glBindTexture(m_texture_type, m_ID);
    }

    void Texture::Unbind()
    {
        glBindTexture(m_texture_type, 0);
    }  

    char* Texture::m_Get_texture_path(const std::string& fname)
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
}
