#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Light
{
public:
		Light() :colour(1.0f, 1.0f, 1.0f) {}
		Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity)
		: colour(red, green, blue) { ambientIntensity = aIntensity; }
	   ~Light() {}

   void UseLight(GLfloat ambientIntnsityLocation, GLfloat ambientColourLocation);

private:
	glm::vec3	colour;
	 GLfloat	ambientIntensity { 1.0f };
};

