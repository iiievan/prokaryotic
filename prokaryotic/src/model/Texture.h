#ifndef CELL_SHADING_TEXTURE_H
#define CELL_SHADING_TEXTURE_H

#include <GLAD/glad.h>

namespace PROKARYOTIC
{

    class Texture
    {
    public:
        Texture(bool mipmapping = false) { m_Mipmapping = mipmapping; }
        ~Texture() {}

        void  Generate(unsigned int width, GLenum internalFormat, GLenum format, GLenum type, void* data);      // 1D texture generation    
        void  Generate(unsigned int width, unsigned int height, GLenum internalFormat, GLenum format, GLenum type, void* data);     // 2D texture generation    
        void  Generate(unsigned int width, unsigned int height, unsigned int depth, GLenum internalFormat, GLenum format, GLenum type, void* data);     // 3D texture generation

        void  Resize(unsigned int width, unsigned int height = 0, unsigned int depth = 0);  // resizes the texture; allocates new (empty) texture memory

        void  Bind(int unit = -1);
        void  Unbind();

        // update relevant texture state
        void  set_GL_Wrap_mode(GLenum wrapMode, bool bind = false);
        void  set_GL_Filter(GLenum filter_min, GLenum filter_max, bool bind = false);

        void  set_ID(unsigned int id) { m_ID = id; }
        void  set_Target(GLenum target) { m_Target = target; }
        void  set_Internal_format(GLenum intformat) { m_Internal_format = intformat; }
        void  set_Format(GLenum format) { m_Format = format; }
        void  set_Type(GLenum type) { m_Type = type; }
        void  set_Filter_min(GLenum filtmin) { m_Filter_min = filtmin; }
        void  set_Filter_max(GLenum filtmax) { m_Filter_max = filtmax; }
        void  set_Wrap_S(GLenum wraps) { m_Wrap_S = wraps; }
        void  set_Wrap_T(GLenum wrapt) { m_Wrap_T = wrapt; }
        void  set_Wrap_R(GLenum wrapr) { m_Wrap_R = wrapr; }
        void  set_Mipmapping(bool mipmapping) { m_Mipmapping = mipmapping; }
        void  set_Width(unsigned int width) { m_Width = width; }
        void  set_Height(unsigned int heigh) { m_Height = heigh; }
        void  set_Depth(unsigned int depth) { m_Depth = depth; }

        unsigned int  get_ID()              const { return m_ID; }
        GLenum  get_Target()          const { return m_Target; }
        GLenum  get_Internal_format() const { return m_Internal_format; }
        GLenum  get_Format()          const { return m_Format; }
        GLenum  get_Type()            const { return m_Type; }
        GLenum  get_Filter_min()      const { return m_Filter_min; }
        GLenum  get_Filter_max()      const { return m_Filter_max; }
        GLenum  get_Wrap_S()          const { return m_Wrap_S; }
        GLenum  get_Wrap_T()          const { return m_Wrap_T; }
        GLenum  get_Wrap_R()          const { return m_Wrap_R; }
        unsigned int  get_Width()           const { return m_Width; }
        unsigned int  get_Height()          const { return m_Height; }
        unsigned int  get_Depth()           const { return m_Depth; }

    private:

        unsigned int  m_ID{ 0xffffffff };

        GLenum  m_Target{ GL_TEXTURE_2D };           // what type of texture we're dealing with
        GLenum  m_Internal_format{ GL_RGBA };                 // number of color components
        GLenum  m_Format{ GL_RGBA };                 // the format each texel is stored in
        GLenum  m_Type{ GL_UNSIGNED_BYTE };
        GLenum  m_Filter_min{ GL_LINEAR_MIPMAP_LINEAR }; // what filter method to use during minification
        GLenum  m_Filter_max{ GL_LINEAR };               // what filter method to use during magnification
        GLenum  m_Wrap_S{ GL_REPEAT };               // wrapping method of the S coordinate
        GLenum  m_Wrap_T{ GL_REPEAT };               // wrapping method of the T coordinate
        GLenum  m_Wrap_R{ GL_REPEAT };               // wrapping method of the R coordinate
        bool  m_Mipmapping{ true };

        unsigned int  m_Width{ 0 };
        unsigned int  m_Height{ 0 };
        unsigned int  m_Depth{ 0 };
    };
}

#endif