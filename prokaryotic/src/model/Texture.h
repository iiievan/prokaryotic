#ifndef CELL_SHADING_TEXTURE_H
#define CELL_SHADING_TEXTURE_H

#include <GLAD/glad.h>

namespace PROKARYOTIC
{
    typedef struct 
    {
             GLenum  texture_type;                              // what type of texture we're dealing with:
                                                                // [ GL_TEXTURE_1D, GL_TEXTURE_2D ,GL_TEXTURE_3D, GL_TEXTURE_CUBE_MAP ] 
      unsigned char* p_image_data {nullptr};                    // texture image data pointer;

       unsigned int  width  {0};                                // Must be 2n + 2 (boundary) for some integer n.
       unsigned int  height {0};                                // The value must be 2 * m * + 2 (boundary) for some integer m.
       unsigned int  depth  {0};

             GLenum  internal_format;                           // number of color components:
                                                                // [GL_ALPHA, GL_ALPHA4, GL_ALPHA8, GL_ALPHA12, GL_ALPHA16, GL_LUMINANCE, GL_LUMINANCE4, GL_LUMINANCE8, GL_LUMINANCE12, GL_LUMINANCE16,
                                                                //  GL_LUMINANCE_ALPHA, GL_LUMINANCE4_ALPHA4, GL_LUMINANCE6_ALPHA2, GL_LUMINANCE8_ALPHA8, GL_LUMINANCE12_ALPHA4, GL_LUMINANCE12_ALPHA12, 
                                                                //  GL_LUMINANCE16_ALPHA16, GL_INTENSITY GL_INTENSITY4, GL_INTENSITY8, GL_INTENSITY12, GL_INTENSITY16, GL_R3_G3_B2, GL_RGB, GL_RGB4, GL_RGB5, 
                                                                //  GL_RGB8, GL_RGB10, GL_RGB12, GL_RGB16, GL_RGBA, GL_RGBA2, GL_RGBA4, GL_RGB5_A1, GL_RGBA8, GL_RGB10_A2, GL_RGBA12, GL_RGBA16 ]
             GLenum  format;                                    // the format each texel is stored in:
                                                                // [ GL_COLOR_INDEX, GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_RGBA, GL_BGR_EXT, GL_BGRA_EXT, GL_LUMINANCE, GL_LUMINANCE_ALPHA ] 
             GLenum  pixel_datatype { GL_UNSIGNED_BYTE };       // pixel data type:
                                                                // [ GL_UNSIGNED_BYTE, GL_BYTE, GL_BITMAP, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT, GL_INT, GL_FLOAT ]
             GLenum  filter_min { GL_LINEAR_MIPMAP_LINEAR };    // what filter method to use during minification
             GLenum  filter_max { GL_LINEAR };                  // what filter method to use during magnification
             GLenum  wrap_S {0};                                // wrapping method of the S coordinate
             GLenum  wrap_T {0};                                // wrapping method of the T coordinate
             GLenum  wrap_R {0};                                // wrapping method of the R coordinate

               bool  mipmapping { false };
    } texture_param_t;

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