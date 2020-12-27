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
	  void	UseShader()				{ glUseProgram(this->shader); }
	GLuint	GetModelLocation()		{ return this->uniformModel; }
	GLuint	GetProjectionLocation() { return this->uniformProjection; }
	GLuint	getViewLocation()		{ return this->uniformView; }
		   
private:
	     
	std::string readShaderCodeFromFile(const char* shaderPath);
	       void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
	       void compileShaders(const char* vShaderCode, const char* fShaderCode);

		 GLuint shader {0};
		 GLuint uniformModel {0};
		 GLuint uniformProjection {0};
		 GLuint uniformView{ 0 };
};
