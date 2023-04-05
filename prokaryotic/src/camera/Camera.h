#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <vector>
#include <glm/glm.hpp>

namespace PROKARYOTIC
{
    class Camera
    {
    public:
        glm::mat4 Projection { glm::mat4(1.0f) };
        glm::mat4 View       { glm::mat4(1.0f) };

        glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3  Forward = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3       Up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3    Right = glm::vec3(1.0f, 0.0f, 0.0f);

    public:
        Camera() {}

        Camera(unsigned  w, unsigned  h)
        : m_Window_width((float)w),
          m_Window_heigh((float)h)
        { }

        Camera(unsigned  w, unsigned  h, glm::vec3 pos)
        : m_Window_width((float)w),
          m_Window_heigh((float)h),
          Position(pos)
        { }

        Camera(glm::vec3 pos, glm::vec3 frwrd, glm::vec3 up)
        : Position(pos), Forward(frwrd), Up(up)
        {
            update_view();
        }

       ~Camera() { };

        void  set_Projection(float rad, float frustum_strt, float frustum_end);
        void  set_View(glm::vec3  view);
   glm::mat4  get_Position();
        void  update_view();

    private:
       float  m_Window_width;
       float  m_Window_heigh;

   glm::mat4  m_Projection { glm::mat4(1.0f) };
   glm::mat4  m_View       { glm::mat4(1.0f) };
   
    };
}

#endif // _CAMERA_H_