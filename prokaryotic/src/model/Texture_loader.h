#ifndef _TEXTURE_LOADER_
#define _TEXTURE_LOADER_

#include "Application.h"

#include <string>

namespace PROKARYOTIC
{
    class Texture;
    //class Texture_cube;

    class Texture_loader
    {
    public:
        static Texture Load_texture(const std::string& filename, GLenum target, GLenum internalFormat, bool srgb = false);
        static Texture Load_HDR_texture(const std::string& filename);
        static   char* Get_texture_path(const std::string& filename);
        // TODO: read and copy original cubemap order from GL specification
        // static Texture_cube Load_texture_cube(std::string top, std::string bottom, std::string left, std::string right, std::string front, std::string back);
        // assumes default names for cubemap faces
        //static Texture_cube Load_texture_cube(std::string folder);
    private:

    };
}
#endif //_TEXTURE_LOADER_