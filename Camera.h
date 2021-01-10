#ifndef _CAMERA_H
#define _CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <map>
#include <vector>

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 5.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
	// camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// euler Angles
	float Yaw	{ YAW };
	float Pitch	{ PITCH} ;
	// camera options
	float MovementSpeed { SPEED };
	float MouseSensitivity { SENSITIVITY };
	float Zoom { ZOOM };

	// constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		   float yaw = YAW, float pitch = PITCH) 
	: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}
	// constructor with scalar values
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) 
	: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	// returns the view matrix calculated using Euler Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(Position, Position + Front, Up);
	}

	// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void keyControl(std::map<int, GLbyte>& keys, float dT)
	{
		float velocity = MovementSpeed * dT;

		for (std::map<int, GLbyte>::iterator it = keys.begin(); it != keys.end(); ++it)
		{
			if(it->first == GLFW_KEY_W && it->second != GLFW_RELEASE)
			{ Position += Front * velocity; }
			if (it->first == GLFW_KEY_A && it->second != GLFW_RELEASE)
			{ Position -= Right * velocity;	}
			if (it->first == GLFW_KEY_S && it->second != GLFW_RELEASE)
			{ Position -= Front * velocity;	}
			if (it->first == GLFW_KEY_D && it->second != GLFW_RELEASE)
			{ Position += Right * velocity;	}
		}
		//Position.y = 0.0f; // make FPS camera
	}

	// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void mouseControl(glm::vec2 dXdY, GLboolean constrainPitch = true)
	{
		dXdY.x *= MouseSensitivity;
		dXdY.y *= MouseSensitivity;

		Yaw   += dXdY.x;
		Pitch += dXdY.y;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		// update Front, Right and Up Vectors using the updated Euler angles
		updateCameraVectors();
	}

	// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void zoomControl(float dY)
	{
		if (dY != 0.0f)
			Zoom -= (float)dY;

		if (Zoom < 1.0f)
			Zoom = 1.0f;
		if (Zoom > 45.0f)
			Zoom = 45.0f;
	}

private:
	// calculates the front vector from the Camera's (updated) Euler Angles
	void updateCameraVectors()
	{
		// calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);
		// also re-calculate the Right and Up vector
		Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		Up = glm::normalize(glm::cross(Right, Front));
	}
};
#endif // _CAMERA_H
