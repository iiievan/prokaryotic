#ifndef _FRAME_BUFFER_H_
#define _FRAME_BUFFER_H_

#include <GLAD/glad.h>
#include <glm/glm.hpp>

class Frame_buffer 
{
public:
            Frame_buffer(int w, int h);
            Frame_buffer(int w, int h, GLuint texID);
           ~Frame_buffer() {}

      void  use();
      void  clear_to_color(glm::vec4 col);
      void  clear();
            
private:
      GLuint  m_ID { 0 };
         int  m_width;
         int  m_height;
unsigned int  m_rbo { 0 };
};

#endif // _FRAME_BUFFER_H_