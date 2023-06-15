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

        glm::vec3 Position = glm::vec3(0.0f, 0.0f, 3.0f);
        glm::vec3    Front = glm::vec3(0.0f, 0.0f,-1.0f);
        glm::vec3       Up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3    Right = glm::vec3(1.0f, 0.0f, 0.0f);
        glm::vec3 World_up = glm::vec3(0.0f, 1.0f, 0.0f);

    public:
        Camera() 
        {
            set_Projection(m_Zoom, 0.1f, 100.f);
            update_View();
        }

        Camera(unsigned  w, unsigned  h)
        : m_Window_width((float)w),
          m_Window_heigh((float)h)
        {
           set_Projection(m_Zoom, 0.1f, 100.f);
           update_View();
        }

        Camera(unsigned  w, unsigned  h, glm::vec3 pos)
        : m_Window_width((float)w),
          m_Window_heigh((float)h),
          Position(pos)
        {
            set_Projection(m_Zoom, 0.1f, 100.f);
            update_View();
        }

        Camera(glm::vec3 pos, glm::vec3 frnt, glm::vec3 up)
        : Position(pos), Front(frnt), Up(up)
        {
            set_Projection(m_Zoom, 0.1f, 100.f);
            update_View();
        }

             ~Camera() { };

        void  set_Projection(float degrees, float frustum_strt, float frustum_end);
        void  set_View(glm::vec3  view);
   glm::mat4  get_Position();   // for vec3 position just use public glm::vec3 Position
        void  update_View();

        void  set_true_FPS() { m_TRUE_FPS = true; }
        void  set_floating() { m_TRUE_FPS = false; }

        inline  void  process_mouse(float x_offset, float y_offset, bool constrain_pitch = false)
        {
            glm::vec3 front;

            x_offset *= m_Mouse_sensitivity;
            y_offset *= m_Mouse_sensitivity;

            m_Yaw += x_offset;
            m_Pitch += y_offset;

            // make sure that when pitch is out of bounds, screen doesn't get flipped
            if (constrain_pitch)
            {
                if (m_Yaw > 89.0f)
                    m_Yaw = 89.0f;
                if (m_Yaw < -89.0f)
                    m_Yaw = -89.0f;
            }

            // update Front, Right and Up Vectors using the updated Euler angle
            front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
            front.y = sin(glm::radians(m_Pitch));
            front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

            Front = glm::normalize(front);

            // also re-calculate the Right and Up vector
            Right = glm::normalize(glm::cross(Front, World_up));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
            Up = glm::normalize(glm::cross(Right, Front));
        }

        inline void process_scroll(float y_offset)
        {
            m_Zoom -= static_cast<float>(y_offset);

            if (m_Zoom < 1.0f)
                m_Zoom = 1.0f;
            if (m_Zoom > 45.0f)
                m_Zoom = 45.0f;
        }

        inline void move_forward(float dt)
        {
            m_velocity = m_Movement_speed * dt;
            Position += Front * m_velocity;

            if (m_TRUE_FPS)
                Position.y = 0.0f; 
        }

        inline void move_backward(float dt)
        {
            m_velocity = m_Movement_speed * dt;
            Position -= Front * m_velocity;

            if (m_TRUE_FPS)
                Position.y = 0.0f;
        }

        inline void move_left(float dt)
        {
            m_velocity = m_Movement_speed * dt;
            Position -= Right * m_velocity;

            if (m_TRUE_FPS)
                Position.y = 0.0f;
        }

        inline void move_right(float dt)
        {
            m_velocity = m_Movement_speed * dt;
            Position += Right * m_velocity;

            if(m_TRUE_FPS)
                Position.y = 0.0f;
        }

    private:
        
       float  m_Window_width;
       float  m_Window_heigh;

       // euler Angles
       float m_Pitch { 0.0f };      // тангаж   (сверху вниз)
       float m_Yaw   { -90.0f };    // рыскание (слева на право)
       //float m_Roll  { 0.0f };    // крен ( когда одно крыло выше другого)

       // camera options
       float  m_Movement_speed    { 5.0f };
       float  m_velocity          { 0.0f };
       float  m_Mouse_sensitivity { 0.1f };
       float  m_Zoom              { 45.0f }; 

        bool  m_TRUE_FPS          { false };

        inline glm::mat4 m_look_at(glm::vec3 position, glm::vec3 target, glm::vec3 world_Up)
        {
            glm::mat4  frame = glm::mat4(1.0f);
            glm::mat4  translate = glm::mat4(1.0f);

            glm::vec3  forward = glm::normalize(target - position);
            glm::vec3    right = glm::normalize(glm::cross(forward, world_Up));
            glm::vec3       up = glm::cross(right, forward);

            frame[0].x = right.x;
            frame[0].y = right.y;
            frame[0].z = right.z;
            frame[1].x = up.x;
            frame[1].y = up.y;
            frame[1].z = up.z;

            frame[2].x = -forward.x;
            frame[2].y = -forward.y;
            frame[2].z = -forward.z;

            frame = glm::transpose(frame);

            translate[3].x = -position.x;
            translate[3].y = -position.y;
            translate[3].z = -position.z;

            return frame * translate;
        }

    };
}

#endif // _CAMERA_H_