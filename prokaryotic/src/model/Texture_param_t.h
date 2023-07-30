#ifndef _TEXTURE_LOADER_
#define _TEXTURE_LOADER_

#include "Application.h"

#include <string>

namespace PROKARYOTIC
{
    template <GLenum T = GL_TEXTURE_2D>
    struct Texture_param_t
    {
      unsigned char* p_image_data {nullptr};                    // texture image data pointer;
                int  width  {0};                                // Must be 2n + 2 (boundary) for some integer n.
                int  height {0};                                // The value must be 2 * m * + 2 (boundary) for some integer m.
                int  depth  {0};
             GLenum  internal_format{};                           // number of color components:
                                                                // [GL_ALPHA, GL_ALPHA4, GL_ALPHA8, GL_ALPHA12, GL_ALPHA16, GL_LUMINANCE, GL_LUMINANCE4, GL_LUMINANCE8, GL_LUMINANCE12, GL_LUMINANCE16,
                                                                //  GL_LUMINANCE_ALPHA, GL_LUMINANCE4_ALPHA4, GL_LUMINANCE6_ALPHA2, GL_LUMINANCE8_ALPHA8, GL_LUMINANCE12_ALPHA4, GL_LUMINANCE12_ALPHA12, 
                                                                //  GL_LUMINANCE16_ALPHA16, GL_INTENSITY GL_INTENSITY4, GL_INTENSITY8, GL_INTENSITY12, GL_INTENSITY16, GL_R3_G3_B2, GL_RGB, GL_RGB4, GL_RGB5, 
                                                                //  GL_RGB8, GL_RGB10, GL_RGB12, GL_RGB16, GL_RGBA, GL_RGBA2, GL_RGBA4, GL_RGB5_A1, GL_RGBA8, GL_RGB10_A2, GL_RGBA12, GL_RGBA16 ]
             GLenum  format;                                    // the format each texel is stored in:
                                                                // [ GL_COLOR_INDEX, GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_RGBA, GL_BGR_EXT, GL_BGRA_EXT, GL_LUMINANCE, GL_LUMINANCE_ALPHA ] 
             GLenum  pixel_datatype {GL_UNSIGNED_BYTE};         // pixel data type:
                                                                // [ GL_UNSIGNED_BYTE, GL_BYTE, GL_BITMAP, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT, GL_INT, GL_FLOAT ]
             
             
             GLenum  filter_min { GL_LINEAR_MIPMAP_LINEAR };    // what filter method to use during minification
             GLenum  filter_max { GL_LINEAR };                  // what filter method to use during magnification
             GLenum  wrap_S {0};                                // wrapping method of the S coordinate
             GLenum  wrap_T {0};                                // wrapping method of the T coordinate
             GLenum  wrap_R {0};                                // wrapping method of the R coordinate

               bool  mipmapping { false };
               bool  srgb;

               template<T = GL_TEXTURE_1D>
               Texture_param_t(std::string  fname, bool srgb = false)
               template<T = GL_TEXTURE_2D>
               Texture_param_t(std::string  fname, bool srgb = false)
               template<T = GL_TEXTURE_3D>
               Texture_param_t(std::string  fname, bool srgb = false)
               template<T = GL_TEXTURE_CUBE_MAP>
               Texture_param_t(std::string  fname, bool srgb = false)
         char* Get_texture_path(const std::string& fname);
    };
}
#endif //_TEXTURE_LOADER_