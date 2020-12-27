#include "Window.h"

int Window::initialize()
{
	if (!glfwInit())
	{
		std::cerr << "GLFW library load failed...\n";
		glfwTerminate();
		return 1;
	}

	// Setup GLFW Window properties

	// OpenGL Version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// OpenGL profile without backwards compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// OpenGL profile allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mainWindow = glfwCreateWindow(width, height, "Main window", NULL, NULL);
	if (!mainWindow)
	{
		std::cerr << "GLFW window creation failed...\n";
		glfwTerminate();
		return 1;
	}

	// OpenGL viewport dimensions
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	glewExperimental = GLU_TRUE;

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		std::cerr << "GLEW initialization failed...\n";
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	// Setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	return 0;
}
