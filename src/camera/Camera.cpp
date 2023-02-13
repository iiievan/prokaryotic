#include"camera/Camera.h"
#include <glm/gtc/matrix_transform.hpp>

void  Camera::set_Projection(float rad, float frustum_strt, float frustum_end)
{
    m_Projection = glm::perspective(rad, m_Window_width / m_Window_heigh, frustum_strt, frustum_end);
}

void  Camera::set_View(glm::vec3  view)
{
    glm::mat4 identity_matrix = glm::mat4(1.0f);

    // note that we're translating the scene in the reverse direction of where we want to move
    m_View = glm::translate(identity_matrix, view);    
}

void  Camera::set_Position(glm::mat4  pos)
{
    m_Position = pos;    
}

void  Camera::Rotate(float  radians, glm::vec3 axis)
{
    m_Position = glm::rotate(m_Position, radians, axis);    
}