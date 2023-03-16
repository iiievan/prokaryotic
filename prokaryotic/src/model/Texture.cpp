#include "texture.h"

#include <assert.h>

namespace PROKARYOTIC
{

    void Texture::Generate(unsigned int width, GLenum internalFormat, GLenum format, GLenum type, void* data)
    {
        glGenTextures(1, &m_ID);

        m_Width = width;
        m_Height = 0;
        m_Depth = 0;
        m_Internal_format = internalFormat;
        m_Format = format;
        m_Type = type;

        assert(m_Target == GL_TEXTURE_1D);
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

        assert(m_Target == GL_TEXTURE_2D);
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

        assert(m_Target == GL_TEXTURE_3D);
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

    void Texture::Bind(int unit)
    {
        if (unit >= 0)
            glActiveTexture(GL_TEXTURE0 + unit);

        glBindTexture(m_Target, m_ID);
    }

    void Texture::Unbind()
    {
        glBindTexture(m_Target, 0);
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
