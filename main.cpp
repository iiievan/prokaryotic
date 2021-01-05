#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h> 



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, int key, int scancode, int action, int mods);

//window dimensions
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = 
"#version 330 core										\n"
"layout (location = 0) in vec3 aPos;					\n"
"void main()											\n"
"{														\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);	\n"
"}\0";

const char* fragmentShaderSourceOrange = 
"#version 330 core										\n"
"out vec4 FragColor;									\n"
"void main()											\n"
"{														\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);			\n"
"}\n\0";

const char* fragmentShaderSourceYellow =
"#version 330 core										\n"
"out vec4 FragColor;									\n"
"void main()											\n"
"{														\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);			\n"
"}\n\0";

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, processInput);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}	

	
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);	//vertex shader	
	int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER); // fragment shader
	int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER); // fragment shader
	int shaderProgramOrange = glCreateProgram();
	int shaderProgramYellow = glCreateProgram();
	int success;
	char infoLog[512];
	unsigned int VBO[2], VAO[2];

	float firstTriangle[] = 
	{
		-1.0f, -1.0f, 0.0f,  // first triangle left
		 0.0f, -1.0f, 0.0f,  // first triangle right
		-0.5f,  0.0f, 0.0f,  // first triangle top
	};

	float secondTriangle[] =
	{
	   -0.5f, 0.0f, 0.0f,  // second triangle left 
		0.5f, 0.0f, 0.0f,  // second triangle right
		0.0f, -1.0f, 0.0f  // second triangle bottom
	};

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glShaderSource(fragmentShaderOrange, 1, &fragmentShaderSourceOrange, NULL);
	glCompileShader(fragmentShaderOrange);

	glGetShaderiv(fragmentShaderOrange, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderOrange, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSourceYellow, NULL);
	glCompileShader(fragmentShaderYellow);

	glGetShaderiv(fragmentShaderOrange, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderOrange, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// link shaders	
	glAttachShader(shaderProgramOrange, vertexShader);
	glAttachShader(shaderProgramOrange, fragmentShaderOrange);
	glLinkProgram(shaderProgramOrange);	

	glGetProgramiv(shaderProgramOrange, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramOrange, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, fragmentShaderYellow);
	glLinkProgram(shaderProgramYellow);

	glGetProgramiv(shaderProgramYellow, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramYellow, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShaderOrange);
	glDeleteShader(fragmentShaderYellow);

	
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);	// поскольку данные вершин плотно упакованы, мы также можем указать 0 в качестве шага атрибута вершины, 
																	// чтобы OpenGL мог это выяснить 3 * sizeof(float) - Тоже работает.
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// рисуем желтый треугольник
		glUseProgram(shaderProgramYellow);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// рисуем оранжевый треугольник
		glUseProgram(shaderProgramOrange);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// deallocate all resources
	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
	glDeleteProgram(shaderProgramOrange);
	
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static GLboolean wireframe { GL_FALSE }; // для отображения режима каркаса.

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_FILL : GL_LINE);
		wireframe = !wireframe;
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}