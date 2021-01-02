#include "PointLight.h"


void PointLight::UseLight(GLfloat ambientIntnsityLocation, GLfloat ambientColourLocation, 
						  GLfloat diffuseIntensityLocation, GLfloat positionLocation, 
	                      GLfloat constantLocation, GLfloat linearLocation, GLfloat exponentLocation)
{
	glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
	glUniform1f(ambientIntnsityLocation, ambientIntensity);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform1f(constantLocation, constant);
	glUniform1f(linearLocation, linear);
	glUniform1f(exponentLocation, exponent);
}
