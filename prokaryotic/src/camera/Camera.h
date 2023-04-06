#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <vector>
#include <glm/glm.hpp>

namespace PROKARYOTIC
{
    enum e_Cam_Move
    {
        CAM_FORWARD,
        CAM_BACKWARD,
        CAM_LEFT,
        CAM_RIGHT
    };

    class Camera
    {
    public:
        glm::mat4 Projection { glm::mat4(1.0f) };
        glm::mat4 View       { glm::mat4(1.0f) };

        glm::vec3 Position = glm::vec3(0.0f, 0.0f, 3.0f);
        glm::vec3    Front = glm::vec3(0.0f, 0.0f,-1.0f);
        glm::vec3       Up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3    Right = glm::vec3(1.0f, 0.0f, 0.0f);
        glm::vec3 World_up = glm::vec3(0.0f, 1.0f, 0.0f);;

    public:
        Camera() 
        {
            set_Projection(m_Zoom, 0.1f, 100.f);
            update_view();
        }

        Camera(unsigned  w, unsigned  h)
        : m_Window_width((float)w),
          m_Window_heigh((float)h)
        {
           set_Projection(m_Zoom, 0.1f, 100.f);
           update_view();
        }

        Camera(unsigned  w, unsigned  h, glm::vec3 pos)
        : m_Window_width((float)w),
          m_Window_heigh((float)h),
          Position(pos)
        {
            set_Projection(m_Zoom, 0.1f, 100.f);
            update_view();
        }

        Camera(glm::vec3 pos, glm::vec3 frnt, glm::vec3 up)
        : Position(pos), Front(frnt), Up(up)
        {
            set_Projection(m_Zoom, 0.1f, 100.f);
            update_view();
        }

       ~Camera() { };

        void  set_Projection(float degrees, float frustum_strt, float frustum_end);
        void  set_View(glm::vec3  view);
   glm::mat4  get_Position();
        void  update_view();
        void  process_keyboard(e_Cam_Move dir, float dT);
        void  process_mouse(float x_offset, float y_offset, bool constrain_pitch = true);
        void  process_scroll(float y_offset);

    private:
        void  m_update_camera_vectors();
        
       float  m_Window_width;
       float  m_Window_heigh;

       // euler Angles
       float m_Pitch { 0.0f };   // тангаж   (сверху вниз)
       float m_Yaw   { -90.0f }; // рыскание (слева на право)
       float m_Roll  { 0.0f };   // крен ( когда одно крыло выше другого)

       // camera options
       float m_Movement_speed    { 5.0f };
       float m_Mouse_sensitivity { 0.1f };
       float m_Zoom              { 45.0f };
   
    };
}

#endif // _CAMERA_H_