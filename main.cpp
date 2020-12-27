#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cmath>

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

// Vertex Shader
static const char* vShader = "shaders/vertex.shader";

// Fragment Shader
static const char* fShader = "shaders/fragment.shader";


void CreateObject() 
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

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj2);
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

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int main()
{
	GLuint uniformModel, uniformProjection;

	mainWindow.initialize();	

	CreateObject();
	CreateShaders();

	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / (GLfloat)mainWindow.getBufferHeight(), 1.0f, 100.0f);

	// loop until window is closed
	while (!mainWindow.getShouldClose())
	{
		// Handle user input events(keyboard, mouse etc.)
		glfwPollEvents();

		// Clear Window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();

		glm::mat4 model;	// model matrix is full of zeroes

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));	//just multiplies model matrix with a Уtranslation matrixФ and dot produc it to vec3
		model = glm::rotate(model, 60.0f * toRadians, glm::vec3(0.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)); // матрица не может быть на пр€мую передана в шейдер, поэтому передаем указатель на нее
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection)); // матрица не может быть на пр€мую передана в шейдер, поэтому передаем указатель на нее
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));	//just multiplies model matrix with a Уtranslation matrixФ and dot produc it to vec3
		model = glm::rotate(model, 30.0f * toRadians, glm::vec3(0.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)); // матрица не может быть на пр€мую передана в шейдер, поэтому передаем указатель на нее
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection)); // матрица не может быть на пр€мую передана в шейдер, поэтому передаем указатель на нее
		meshList[1]->RenderMesh();


		glUseProgram(0);
		mainWindow.swapBuffers();
	}


	return 0;
}