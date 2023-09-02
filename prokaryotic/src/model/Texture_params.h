#ifndef _TEXTURE_LOADER_
#define _TEXTURE_LOADER_

#include "Application.h"

#include <string>
#include "stb\stb_image.h"

namespace PROKARYOTIC
{
    // type of texture: [ GL_TEXTURE_1D, GL_TEXTURE_2D ,GL_TEXTURE_3D, GL_TEXTURE_CUBE_MAP ]
    template <GLenum TEXTYPE>
    struct Texture_params
    {
        unsigned char* p_image_data{ nullptr };                    // texture image data pointer;
        int  width{ 0 };                                // Must be 2n + 2 (boundary) for some integer n.
        int  height{ 0 };                                // The value must be 2 * m * + 2 (boundary) for some integer m.
        int  depth{ 0 };
        GLenum  internal_format { 0 };                         // number of color components:
                                                           // [GL_ALPHA, GL_ALPHA4, GL_ALPHA8, GL_ALPHA12, GL_ALPHA16, GL_LUMINANCE, GL_LUMINANCE4, GL_LUMINANCE8, GL_LUMINANCE12, GL_LUMINANCE16,
                                                           //  GL_LUMINANCE_ALPHA, GL_LUMINANCE4_ALPHA4, GL_LUMINANCE6_ALPHA2, GL_LUMINANCE8_ALPHA8, GL_LUMINANCE12_ALPHA4, GL_LUMINANCE12_ALPHA12, 
                                                           //  GL_LUMINANCE16_ALPHA16, GL_INTENSITY GL_INTENSITY4, GL_INTENSITY8, GL_INTENSITY12, GL_INTENSITY16, GL_R3_G3_B2, GL_RGB, GL_RGB4, GL_RGB5, 
                                                           //  GL_RGB8, GL_RGB10, GL_RGB12, GL_RGB16, GL_RGBA, GL_RGBA2, GL_RGBA4, GL_RGB5_A1, GL_RGBA8, GL_RGB10_A2, GL_RGBA12, GL_RGBA16 ]
        GLenum  format;                                    // the format each texel is stored in:
                                                           // [ GL_COLOR_INDEX, GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_RGBA, GL_BGR_EXT, GL_BGRA_EXT, GL_LUMINANCE, GL_LUMINANCE_ALPHA ] 
        GLenum  pixel_datatype{ GL_UNSIGNED_BYTE };         // pixel data type:
                                                           // [ GL_UNSIGNED_BYTE, GL_BYTE, GL_BITMAP, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT, GL_INT, GL_FLOAT ]


        GLenum  filter_min{ GL_LINEAR_MIPMAP_LINEAR };    // what filter method to use during minification
        GLenum  filter_max{ GL_LINEAR };                  // what filter method to use during magnification [GL_NEAREST , GL_LINEAR ]
        GLenum  wrap_S{ 0 };                              // wrapping method of the S coordinate
        GLenum  wrap_T{ 0 };                              // wrapping method of the T coordinate
        GLenum  wrap_R{ 0 };                              // wrapping method of the R coordinate
                                                          // wrapping methods: [GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER]

        bool  mipmapping{ true };

        Texture_params(std::string  fname, GLenum intform, bool srgb = false)   // 2D-type fills width, hight, internal_format, format, srgb fields automatically
        {
            char* path = Get_texture_path(fname);
            int  nrComponents;

            switch (intform)
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
            p_image_data = stbi_load(path, &width, &height, &nrComponents, 0);

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
                printf("Texture failed to load at path:%s.", path);            
        }

        template<GLenum TEXTYPE = GL_TEXTURE_1D>
        inline void  set_wrap(GLenum S)
        {
            wrap_S = S;
            wrap_T = 0;
            wrap_R = 0;
        }

        template<GLenum TEXTYPE = GL_TEXTURE_2D>
        inline void  set_wrap(GLenum S, GLenum T)
        {
            wrap_S = S;
            wrap_T = T;
            wrap_R = 0;
        }

        template<GLenum TEXTYPE = GL_TEXTURE_3D>
        inline void  set_wrap(GLenum S, GLenum T, GLenum R)
        {
            wrap_S = S;
            wrap_T = T;
            wrap_R = R;
        }

        char* Get_texture_path(const std::string& fname)
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
    };
}
#endif //_TEXTURE_LOADER_