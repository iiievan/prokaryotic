#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Window.h"



const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;

GLuint VAO, VBO, IBO, shader, uniformModel, uniformProjection;

bool direction	{ true };
float triOffset	{ 0.0f };
float triMaxoffset = 0.7f;
float triIncrement = 0.005f;

float curAngle = 0.0f;

 bool sizeDirection { true };
float curSize = 0.4f;
float maxSize	{ 0.8f };
float minSize	{ 0.1f };

static const char* vShader =
"																		\n\
#version 330															\n\
																		\n\
layout(location = 0) in vec3 pos;										\n\
																		\n\
out vec4 vCol;															\n\
																		\n\
uniform mat4 model;														\n\
uniform mat4 projection;												\n\
																		\n\
void main()																\n\
{																		\n\
	gl_Position = projection * model * vec4(pos, 1.0);					\n\
	vCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);							\n\
}";

// Fragment Shader
static const char* fShader =
"																		\n\
#version 330															\n\
																		\n\
in vec4 vCol;															\n\
																		\n\
out vec4 colour;														\n\
																		\n\
void main()																\n\
{																		\n\
	colour = vCol;														\n\
}";

void CreateTriangle() 
{
	// индексы вершин, образующих пирамиду с треугольным основанием.
	unsigned int indices[] =
	{
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] =
	{
	   -1.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// free VBO and VAO and IBO ID's, другими словами освобождаем буфферы
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024]{ 0 };

	glLinkProgram(theShader);
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), nullptr, eLog);
		printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

void CompileShaders()
{
	shader = glCreateProgram();
	if (!shader)
	{
		printf("Error creating shader program!\n");
		return;
	}

	AddShader(shader, vShader, GL_VERTEX_SHADER);
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] { 0 };

	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), nullptr, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}

	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), nullptr, eLog);
		printf("Error validate program: '%s'\n", eLog);
		return;
	}

	uniformModel = glGetUniformLocation(shader, "model");
	uniformProjection = glGetUniformLocation(shader, "projection");
}

int main()
{
	mainWindow.initialize();	

	CreateTriangle();
	CompileShaders();

	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / (GLfloat)mainWindow.getBufferHeight(), 1.0f, 100.0f);

	// loop until window is closed
	while (!mainWindow.getShouldClose())
	{
		// Handle user input events(keyboard, mouse etc.)
		glfwPollEvents();

		if (direction)
		{
			triOffset += triIncrement;
		}
		else
		{
			triOffset -= triIncrement;
		}

		if (abs(triOffset) >= triMaxoffset)
		{
			direction = !direction;
		}

		curAngle += 0.5f;

		if (curAngle >= 360)
		{
			curAngle -= 360;
		}

		if (sizeDirection)
		{
			curSize += 0.01f;
		}
		else
		{
			curSize -= 0.01f;
		}

		if (curSize >= maxSize || 
			curSize <= minSize)
		{
			sizeDirection = !sizeDirection;
		}

		// Clear Window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shader);

		glm::mat4 model;	// model matrix is full of zeroes		
		model = glm::translate(model, glm::vec3(triOffset, 0.0f, -2.5f));	//just multiplies model matrix with a Уtranslation matrixФ and dot produc it to vec3
		//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)); // матрица не может быть на пр€мую передана в шейдер, поэтому передаем указатель на нее
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection)); // матрица не может быть на пр€мую передана в шейдер, поэтому передаем указатель на нее

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glUseProgram(0);

		mainWindow.swapBuffers();
	}


	return 0;
}