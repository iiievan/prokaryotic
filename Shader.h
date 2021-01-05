#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:	
	Shader(const char* vertexPath, const char* fragmentPath);	
	//~Shader()  { glDeleteProgram(ID); }

	void use() { glUseProgram(ID); }
	void setBool(const std::string &name, bool value)	const { glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); }
	void setInt(const std::string &name, int value)		const { glUniform1i(glGetUniformLocation(ID, name.c_str()), value); }
	void setFloat(const std::string &name, float value) const { glUniform1f(glGetUniformLocation(ID, name.c_str()), value); }

	unsigned int ID;
private:
	void checkCompileErrors(unsigned int shader, std::string type);
};

#endif // SHADER_H
