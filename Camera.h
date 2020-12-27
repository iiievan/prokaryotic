#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

class Camera
{
public:
				Camera() {}
				Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMS, GLfloat startTS);
			   ~Camera();

		void	keyControl(bool* keys, GLfloat dT);
		void	mouseControl(GLfloat dX, GLfloat dY);
   glm::mat4	calculateViewMatrix();

private:
	glm::vec3	position;
	glm::vec3	front;
	glm::vec3	up;
	glm::vec3	right;
	glm::vec3	worldUp;

	 GLfloat	yaw;	// look left and right
	 GLfloat	pitch;	// look up and down

	 GLfloat	moveSpeed;
	 GLfloat	turnSpeed;

	    void	update();
};

