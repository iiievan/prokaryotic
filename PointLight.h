#pragma once
#include "Light.h"

class PointLight : public Light
{
public:
	PointLight() : Light(), position(0.0f, 0.0f,0.0f) {}

	PointLight(GLfloat red, GLfloat green, GLfloat blue,
			   GLfloat aIntensity, GLfloat dIntensity,
			   GLfloat xPos, GLfloat yPos, GLfloat zPos,
			   GLfloat con, GLfloat lin, GLfloat exp)
	: Light(red, green, blue, aIntensity, dIntensity), position(xPos, yPos, zPos) 
	{
		constant = con;
		linear = lin;
		exponent = exp;
	}

	~PointLight() {}

	void UseLight(GLfloat ambientIntnsityLocation, GLfloat ambientColourLocation,
				  GLfloat diffuseIntensityLocation, GLfloat positionLocation,
				  GLfloat constantLocation, GLfloat linearLocation, GLfloat exponentLocation);
private:
	glm::vec3	position;

	  // constituents of light attenuation
	  GLfloat	constant	{ 1.0f };
	  GLfloat	linear		{ 0.0f };
	  GLfloat	exponent	{ 0.0f };	
};

