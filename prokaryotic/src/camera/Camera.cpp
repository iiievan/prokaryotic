#include"camera/Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include<GLFW/glfw3.h>

namespace PROKARYOTIC
{
    void  Camera::set_Projection(float rad, float frustum_strt, float frustum_end)
    {
        this->Projection = glm::perspective(rad, m_Window_width / m_Window_heigh, frustum_strt, frustum_end);
    }

    void  Camera::set_View(glm::vec3  view)
    {
        glm::mat4 model = glm::mat4(1.0f);

        // note that we're translating the scene in the reverse direction of where we want to move
        this->View = glm::translate(model, view);
    }

    glm::mat4  Camera::get_Position()
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, this->Position);

        return model;
    }

    void  Camera::update_view()
    {
        this->View = glm::lookAt(this->Position, this->Position + this->Forward, this->Up);   
    }
}