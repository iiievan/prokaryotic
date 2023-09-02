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

#include "model/Texture_params.h"

namespace PROKARYOTIC
{   
    template <GLenum TEXTYPE>
    struct Texture_params;

    class Texture
    {
    public:
               Texture(Texture_params<GL_TEXTURE_1D>  params);
               Texture(Texture_params<GL_TEXTURE_2D>  params);
               Texture(Texture_params<GL_TEXTURE_3D>  params);
               Texture(Texture_params<GL_TEXTURE_CUBE_MAP>  params);
               
               ~Texture() {}
               
         void  Bind(int i = -1);     // i - number of array of texture units ~ 8 arrays for simultaneously texture drawing;
         void  Unbind();
 
 unsigned int  get_ID()     const { return m_ID; }
       GLenum  get_Type()   const { return m_texture_type; }

    private:

         unsigned int  m_ID{ 0xffffffff };
               GLenum  m_texture_type;
    };
}

#endif