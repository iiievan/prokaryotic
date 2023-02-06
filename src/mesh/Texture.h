#ifndef CELL_SHADING_TEXTURE_H
#define CELL_SHADING_TEXTURE_H

#include <GLAD/glad.h>


class Texture
{
public:
              Texture(){}
             ~Texture(){}
        
        void  Generate(unsigned int width, GLenum internalFormat, GLenum format, GLenum type, void* data);      // 1D texture generation    
        void  Generate(unsigned int width, unsigned int height, GLenum internalFormat, GLenum format, GLenum type, void* data);     // 2D texture generation    
        void  Generate(unsigned int width, unsigned int height, unsigned int depth, GLenum internalFormat, GLenum format, GLenum type, void* data);     // 3D texture generation
        
        void  Resize(unsigned int width, unsigned int height = 0, unsigned int depth = 0);  // resizes the texture; allocates new (empty) texture memory
    
        void  Bind(int unit = -1);
        void  Unbind();
    
        // update relevant texture state
        void  set_Wrap_mode(GLenum wrapMode, bool bind = false);
        void  set_Filter_min(GLenum filter, bool bind = false);
        void  set_Filter_max(GLenum filter, bool bind = false);

private:
    // TODO: these should be private and only accessed w/ getters/setters s.t. we can 
    // directly change the texture state where relevant from within the setters.

unsigned int  m_ID;

      GLenum  m_Target              { GL_TEXTURE_2D };           // what type of texture we're dealing with
      GLenum  m_Internation_format  { GL_RGBA };                 // number of color components
      GLenum  m_Format              { GL_RGBA };                 // the format each texel is stored in
      GLenum  m_Type                { GL_UNSIGNED_BYTE };
      GLenum  m_Filter_min          { GL_LINEAR_MIPMAP_LINEAR }; // what filter method to use during minification
      GLenum  m_Filter_max          { GL_LINEAR };               // what filter method to use during magnification
      GLenum  m_Wrap_S              { GL_REPEAT };               // wrapping method of the S coordinate
      GLenum  m_Wrap_T              { GL_REPEAT };               // wrapping method of the T coordinate
      GLenum  m_Wrap_R              { GL_REPEAT };               // wrapping method of the R coordinate
        bool  m_Mipmapping          { true };

unsigned int  m_Width               {0};
unsigned int  m_Height              {0};
unsigned int  m_Depth               {0};
};


#endif