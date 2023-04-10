#include"camera/Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include<GLFW/glfw3.h>

namespace PROKARYOTIC
{
    void  Camera::set_Projection(float degrees, float frustum_strt, float frustum_end)
    {
		if (degrees >= 0.0f)
			m_Zoom = degrees;

        this->Projection = glm::perspective(glm::radians(m_Zoom), m_Window_width / m_Window_heigh, frustum_strt, frustum_end);
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

    void  Camera::update_View()
    {
        this->View = glm::lookAt(this->Position, this->Position + this->Front, this->Up);
    }
}