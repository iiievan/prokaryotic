#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <vector>
#include <glm/glm.hpp>

class Camera
{
public:
                Camera(unsigned  w , unsigned  h) 
                : m_Window_width((float)w), 
                  m_Window_heigh((float)h)
                { }
                Camera(unsigned  w , unsigned  h, glm::mat4 pos) 
                : m_Window_width((float)w), 
                  m_Window_heigh((float)h),
                  m_Position(pos) 
                { }
               ~Camera() { };

         void  set_Projection(float rad, float frustum_strt, float frustum_end);
         void  set_View(glm::vec3  view);
         void  set_Position(glm::mat4  pos);
         void  Rotate(float  radians, glm::vec3 axis);

    glm::mat4  get_Projection() const { return m_Projection; }
    glm::mat4  get_View()       const { return m_View; }
    glm::mat4  get_Position()   const { return m_Position; }

private:
        float  m_Window_width;
        float  m_Window_heigh;

    glm::mat4  m_Projection { glm::mat4(1.0f) };
    glm::mat4  m_View       { glm::mat4(1.0f) };
    glm::mat4  m_Position   { glm::mat4(1.0f) };      // Camera Position

};

#endif // _CAMERA_H_