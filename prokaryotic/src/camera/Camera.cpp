#include"camera/Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include<GLFW/glfw3.h>

namespace PROKARYOTIC
{
    void  Camera::set_Projection(float degrees, float frustum_strt, float frustum_end)
    {
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

    void  Camera::update_view()
    {
        this->View = glm::lookAt(this->Position, this->Position + this->Front, this->Up);
    }

	void Camera::process_keyboard(e_Cam_Move dir, float dT)
	{
		float velocity = m_Movement_speed * dT;

		if (dir == CAM_FORWARD)
			Position += Front * velocity;
		if (dir == CAM_BACKWARD)
			Position -= Front * velocity;
		if (dir == CAM_LEFT)
			Position -= Right * velocity;
		if (dir == CAM_RIGHT)
			Position += Right * velocity;

		//Position.y = 0.0f; // make FPS camera
	}

	void Camera::process_mouse(float x_offset, float y_offset, bool constrain_pitch = true)
	{
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

		// update Front, Right and Up Vectors using the updated Euler angles
		m_update_camera_vectors();
	}

	void Camera::process_scroll(float y_offset)
	{
		m_Zoom -= static_cast<float>(y_offset);

		if (m_Zoom < 1.0f)
			m_Zoom = 1.0f;
		if (m_Zoom > 45.0f)
			m_Zoom = 45.0f;
	}

	void Camera::m_update_camera_vectors()
	{
		// calculate the new Front vector
		glm::vec3 front;

		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

		Front = glm::normalize(front);

		// also re-calculate the Right and Up vector
		Right = glm::normalize(glm::cross(Front, World_up));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		Up = glm::normalize(glm::cross(Right, Front));
	}
}