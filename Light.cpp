#include "Light.h"



void Light::UseLight(GLfloat ambientIntnsityLocation, GLfloat ambientColourLocation)
{
	glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
	glUniform1f(ambientIntnsityLocation, ambientIntensity);
}
