#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Light
{
public:
		Light() :colour(1.0f, 1.0f, 1.0f), direction(0.0f, -1.0f, 0.0f) {}
		Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
			  GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity)
		: colour(red, green, blue), direction(xDir,yDir,zDir)
		{ 
			ambientIntensity = aIntensity;
			diffuseIntensity = dIntensity;
		}

	   ~Light() {}

   void UseLight(GLfloat ambientIntnsityLocation, GLfloat ambientColourLocation,
				 GLfloat diffuseIntensityLocation, GLfloat directionLocation);

private:
	glm::vec3	colour;
	  GLfloat	ambientIntensity { 1.0f };

	glm::vec3	direction;
	  GLfloat	diffuseIntensity { 0.0f };
};

