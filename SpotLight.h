#pragma once
#include "PointLight.h"

class SpotLight : public PointLight
{
public:
	SpotLight() : PointLight(), direction(0.0f, -1.0f, 0.0f)
	{
		direction = glm::normalize(direction);
	}

	SpotLight(GLfloat red, GLfloat green, GLfloat blue,
			  GLfloat aIntensity, GLfloat dIntensity,
			  GLfloat xPos, GLfloat yPos, GLfloat zPos,
			  GLfloat xDir, GLfloat yDir, GLfloat zDir,
			  GLfloat con, GLfloat lin, GLfloat exp, GLfloat edg)
		: PointLight(red, green, blue, aIntensity, dIntensity, xPos, yPos, zPos, con, lin, exp), direction(xDir, yDir, zDir)
	{
		direction = glm::normalize(direction);
		edge = edg;
		procEdge = cosf(glm::radians(edge));
	}

	~SpotLight() {}

	void UseLight(GLuint ambientIntnsityLocation, GLfloat ambientColourLocation,
				  GLuint diffuseIntensityLocation, GLuint positionLocation, GLuint directionLocation, 
				  GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation, GLuint edgeLocation);

	void SetFlash(glm::vec3 pos, glm::vec3 dir);

private:
	glm::vec3	direction;

	  GLfloat	edge	 {0.0f};
	  GLfloat	procEdge {1.0f};
};

