#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>;

#include "DirectionalLight.h"
#include "PointLight.h"
#include "CommonValues.h"

#pragma once
class Shader
{
public:
			Shader() {}
		   ~Shader() {}
	  void	CreateFromFiles(const char* vShader, const char* fShader);
	  void	UseShader()					  { glUseProgram(shaderID); }
	GLuint	GetModelLocation()			  { return uniformModel; }
	GLuint	GetProjectionLocation()		  { return uniformProjection; }
	GLuint	getViewLocation()			  { return uniformView; }
	GLuint	getEyePositionLocation()	  { return uniformEyePosition; 	}
	GLuint	getAmbientIntencityLocation() { return uniformDirectionalLight.uniformAmbientIntensity; }
	GLuint	getAmbientColourLocation()	  { return uniformDirectionalLight.uniformColour; }
	GLuint	getDiffuseIntensityLocation() { return uniformDirectionalLight.uniformDiffuseIntensity; }
	GLuint	getDirectionLocation()        { return uniformDirectionalLight.uniformDirection; }
	GLuint	getSpecularIntensityLocation(){ return uniformSpecularIntensity; }
	GLuint	getShininessLocation()		  { return uniformShininess; }

	void	setDirectionalLight(DirectionalLight* dLight);
	void	setPointLights(PointLight* pLights, unsigned int lightCount);
			   
private:
			int pointLightCount	{0};
	     
	std::string readShaderCodeFromFile(const char* shaderPath);
	       void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
	       void compileShaders(const char* vShaderCode, const char* fShaderCode);

		 GLuint shaderID						{ 0 };
		 GLuint uniformModel					{ 0 };
		 GLuint uniformProjection				{ 0 };
		 GLuint uniformView						{ 0 };
		 GLuint	uniformEyePosition				{ 0 };

		 GLuint uniformSpecularIntensity		{ 0 };
		 GLuint uniformShininess				{ 0 };

		 struct
		 {
			 GLuint	uniformColour				{ 0 };
			 GLuint uniformAmbientIntensity		{ 0 };
			 GLuint uniformDiffuseIntensity		{ 0 };

			 GLuint uniformDirection			{ 0 };
		 } uniformDirectionalLight;

		 GLuint uniformPointLightCount			{ 0 };

		 struct
		 {
			 GLuint	uniformColour				{ 0 };
			 GLuint uniformAmbientIntensity		{ 0 };
			 GLuint uniformDiffuseIntensity		{ 0 };

			 GLuint uniformPosition				{ 0 };
			 GLuint uniformConstant				{ 0 };
			 GLuint uniformLinear				{ 0 };
			 GLuint uniformExponent				{ 0 };
		 } uniformPointLights[MAX_POINT_LIGHTS];	
};
