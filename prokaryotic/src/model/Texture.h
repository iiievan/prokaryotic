#ifndef CELL_SHADING_TEXTURE_H
#define CELL_SHADING_TEXTURE_H

#include <Shlwapi.h>
#include <io.h> 
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <stdint.h>

#include <GLAD/glad.h>
#include "utils/utils.h"

#include "Application.h"
#include "stb\stb_image.h"

namespace PROKARYOTIC
{   
    class Texture
    {
    public:              
               Texture(GLenum textype, std::string  fname, GLenum intform, bool mipmap, bool srgb);  // textype: [ GL_TEXTURE_1D, GL_TEXTURE_2D ,GL_TEXTURE_3D, GL_TEXTURE_CUBE_MAP ]
               
               ~Texture() {}
               
         void  Bind(int i = -1);     // i - number of array of texture units ~ 8 arrays for simultaneously texture drawing;
         void  Unbind();
 
 unsigned int  get_ID()     const { return m_ID; }
       GLenum  get_Type()   const { return m_texture_type; }

               template<GLenum TEXTYPE = GL_TEXTURE_1D>
               inline void  set_wrap(GLenum S)
               {
                   m_wrap_S = S;
                   m_wrap_T = 0;
                   m_wrap_R = 0;
               }

               template<GLenum TEXTYPE = GL_TEXTURE_2D>
               inline void  set_wrap(GLenum S, GLenum T)
               {
                   m_wrap_S = S;
                   m_wrap_T = T;
                   m_wrap_R = 0;
               }

               template<GLenum TEXTYPE = GL_TEXTURE_3D>
               inline void  set_wrap(GLenum S, GLenum T, GLenum R)
               {
                   m_wrap_S = S;
                   m_wrap_T = T;
                   m_wrap_R = R;
               }

    private:
                 char* m_Get_texture_path(const std::string& fname);

         unsigned int  m_ID;
               GLenum  m_texture_type;                          // textype: [ GL_TEXTURE_1D, GL_TEXTURE_2D ,GL_TEXTURE_3D, GL_TEXTURE_CUBE_MAP ]

               unsigned char* m_p_image_data{ nullptr };          // texture image data pointer;
               int  m_width{ 0 };                                 // Must be 2n + 2 (boundary) for some integer n.
               int  m_height{ 0 };                                // The value must be 2 * m * + 2 (boundary) for some integer m.
               int  m_depth{ 0 };
               GLenum  m_internal_format{ 0 };                      // number of color components:
                                                                  // [GL_ALPHA, GL_ALPHA4, GL_ALPHA8, GL_ALPHA12, GL_ALPHA16, GL_LUMINANCE, GL_LUMINANCE4, GL_LUMINANCE8, GL_LUMINANCE12, GL_LUMINANCE16,
                                                                  //  GL_LUMINANCE_ALPHA, GL_LUMINANCE4_ALPHA4, GL_LUMINANCE6_ALPHA2, GL_LUMINANCE8_ALPHA8, GL_LUMINANCE12_ALPHA4, GL_LUMINANCE12_ALPHA12, 
                                                                  //  GL_LUMINANCE16_ALPHA16, GL_INTENSITY GL_INTENSITY4, GL_INTENSITY8, GL_INTENSITY12, GL_INTENSITY16, GL_R3_G3_B2, GL_RGB, GL_RGB4, GL_RGB5, 
                                                                  //  GL_RGB8, GL_RGB10, GL_RGB12, GL_RGB16, GL_RGBA, GL_RGBA2, GL_RGBA4, GL_RGB5_A1, GL_RGBA8, GL_RGB10_A2, GL_RGBA12, GL_RGBA16 ]
               GLenum  m_format;                                    // the format each texel is stored in:
                                                                  // [ GL_COLOR_INDEX, GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_RGBA, GL_BGR_EXT, GL_BGRA_EXT, GL_LUMINANCE, GL_LUMINANCE_ALPHA ] 
               GLenum  m_pixel_datatype{ GL_UNSIGNED_BYTE };         // pixel data type:
                                                                  // [ GL_UNSIGNED_BYTE, GL_BYTE, GL_BITMAP, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT, GL_INT, GL_FLOAT ]


               GLenum  m_filter_min{ GL_LINEAR_MIPMAP_LINEAR };    // what filter method to use during minification
               GLenum  m_filter_max{ GL_LINEAR };                  // what filter method to use during magnification [GL_NEAREST , GL_LINEAR ]
               GLenum  m_wrap_S{ 0 };                              // wrapping method of the S coordinate
               GLenum  m_wrap_T{ 0 };                              // wrapping method of the T coordinate
               GLenum  m_wrap_R{ 0 };                              // wrapping method of the R coordinate
                                                                 // wrapping methods: [GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER]

               bool  m_mipmapping;
    };
}

#endif