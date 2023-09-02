#include "Texture.h"

#include <assert.h>
#include <string>

namespace PROKARYOTIC
{    
    Texture::Texture(Texture_params<GL_TEXTURE_1D>  params)
    {
        m_texture_type = GL_TEXTURE_1D;
        glGenTextures(1, &m_ID);

        params.set_wrap<GL_TEXTURE_1D>(GL_REPEAT);

        Bind();

        if (params.p_image_data)
        {
            glTexImage1D(m_texture_type, 0, params.internal_format, params.width, 0,
                         params.format, params.pixel_datatype, params.p_image_data);
            glTexParameteri(m_texture_type, GL_TEXTURE_MIN_FILTER, params.filter_max);
            glTexParameteri(m_texture_type, GL_TEXTURE_MAG_FILTER, params.filter_min);
            glTexParameteri(m_texture_type, GL_TEXTURE_WRAP_S, params.wrap_S);

            if (params.mipmapping)
                glGenerateMipmap(m_texture_type);

            stbi_image_free(params.p_image_data);
        }
        else
            printf("Texture failed to generate at ID:%d.", m_ID);

        Unbind();        
    }

    Texture::Texture(Texture_params<GL_TEXTURE_2D>  params)
    {
        m_texture_type = GL_TEXTURE_2D;

        glGenTextures(1, &m_ID);

        params.set_wrap<GL_TEXTURE_2D>(GL_REPEAT, GL_REPEAT);

        Bind();

        if(params.p_image_data)
        { 
            glTexImage2D(m_texture_type, 0, params.internal_format,
                         params.width, params.height, 0, 
                         params.format, params.pixel_datatype, params.p_image_data);
            glTexParameteri(m_texture_type, GL_TEXTURE_MIN_FILTER, params.filter_max);
            glTexParameteri(m_texture_type, GL_TEXTURE_MAG_FILTER, params.filter_min);
            glTexParameteri(m_texture_type, GL_TEXTURE_WRAP_S, params.wrap_S);
            glTexParameteri(m_texture_type, GL_TEXTURE_WRAP_T, params.wrap_T);

            if (params.mipmapping)
                glGenerateMipmap(m_texture_type);

            stbi_image_free(params.p_image_data);
        }
        else
            printf("Texture failed to generate at ID:%d.", m_ID);

        Unbind();        
    }

    Texture::Texture(Texture_params<GL_TEXTURE_3D>  params)
    {
        m_texture_type = GL_TEXTURE_3D;

        glGenTextures(1, &m_ID);

        params.set_wrap<GL_TEXTURE_3D>(GL_REPEAT, GL_REPEAT, GL_REPEAT);

        Bind();

        if (params.p_image_data)
        {
            glTexImage3D(m_texture_type, 0, params.internal_format,
                        params.width, params.height, params.depth, 0, 
                        params.format, params.pixel_datatype, params.p_image_data);
            glTexParameteri(m_texture_type, GL_TEXTURE_MIN_FILTER, params.filter_max);
            glTexParameteri(m_texture_type, GL_TEXTURE_MAG_FILTER, params.filter_min);
            glTexParameteri(m_texture_type, GL_TEXTURE_WRAP_S, params.wrap_S);
            glTexParameteri(m_texture_type, GL_TEXTURE_WRAP_T, params.wrap_T);
            glTexParameteri(m_texture_type, GL_TEXTURE_WRAP_R, params.wrap_R);

            if (params.mipmapping)
                glGenerateMipmap(m_texture_type);

            stbi_image_free(params.p_image_data);
        }
        else
            printf("Texture failed to generate at ID:%d.", m_ID);

        Unbind();        
    }

    // WARNING: class constructor for CUBE_MAP not finished yet.
    Texture::Texture(Texture_params<GL_TEXTURE_CUBE_MAP>  params)
    {
        m_texture_type = GL_TEXTURE_CUBE_MAP;

        glGenTextures(1, &m_ID);

        //params.set_wrap<GL_TEXTURE_CUBE_MAP>();

        Bind();

        if (params.mipmapping)
            glGenerateMipmap(m_texture_type);

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
}
