#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Light
{
public:
		Light() :colour(1.0f, 1.0f, 1.0f) {}

		Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
			  GLfloat dIntensity)
		: colour(red, green, blue)
		{ 
			ambientIntensity = aIntensity;
			diffuseIntensity = dIntensity;
		}

	   ~Light() {}

protected:
	glm::vec3	colour;
	  GLfloat	ambientIntensity { 1.0f };
	  GLfloat	diffuseIntensity { 0.0f };
};

