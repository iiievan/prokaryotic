#pragma once

#include<GL/glew.h>

class Material
{
public:
			Material()  {}
			Material(GLfloat sIntensity, GLfloat shine)
			:specularIntensity(sIntensity), shininess(shine) {}
			~Material() {}

			void UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation);
private:
	GLfloat	specularIntensity	{ 0.0f };
	GLfloat	shininess			{ 0.0f };
};

