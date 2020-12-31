#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>;

#pragma once
class Shader
{
public:
			Shader() {}
		   ~Shader() {}
	  void	CreateFromFiles(const char* vShader, const char* fShader);
	  void	UseShader()				{ glUseProgram(this->shaderID); }
	GLuint	GetModelLocation()		{ return this->uniformModel; }
	GLuint	GetProjectionLocation() { return this->uniformProjection; }
	GLuint	getViewLocation()		{ return this->uniformView; }
	GLuint	getAmbientIntencityLocation() { return uniformAmbientIntensity; }
	GLuint	getAmbientColourLocation()	  { return uniformAmbientColour; }
	GLuint	getDiffuseIntensityLocation() { return uniformDiffuseIntensity; }
	GLuint	getDirectionLocation()        { return uniformDirection; }
		   
private:
	     
	std::string readShaderCodeFromFile(const char* shaderPath);
	       void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
	       void compileShaders(const char* vShaderCode, const char* fShaderCode);

		 GLuint shaderID				{ 0 };
		 GLuint uniformModel			{ 0 };
		 GLuint uniformProjection		{ 0 };
		 GLuint uniformView				{ 0 };
		 GLuint uniformAmbientIntensity	{ 0 };
		 GLuint uniformAmbientColour	{ 0 };
		 GLuint uniformDiffuseIntensity	{ 0 };
		 GLuint uniformDirection		{ 0 };
};
