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

	// Handle Key + Mouse Input
	createCallbacks();
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //убираем отображение курсора мыши, она только на движения реагирует.

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

	// указатель пользователя указывает на наш класс Window, чтобы можно было вызвать обработчик клавиш handleKeyboard при их нажатии.
	glfwSetWindowUserPointer(mainWindow, this);	

	return 0;
}

GLfloat Window::get_dX()
{
	GLfloat ret = dX;
	           dX = 0.0f;

	return ret;
}

GLfloat Window::get_dY()
{
	GLfloat ret = dY;
	           dY = 0.0f;

	return ret;
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, handleKeyboard);
	glfwSetCursorPosCallback(mainWindow, handleMouse);
}

void Window::handleKeyboard(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0  && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("Pressed: %d\n", key); //for debug
		}
		else
		if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("Released: %d\n", key);  //for debug
		}
	}
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	// инициализируем последние координаты x и y при первом движении мыши
	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->dX = xPos - theWindow->lastX;
	theWindow->dY = theWindow->lastY - yPos; // because y scale is negative

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;

	//printf("X: %.6f, Y: %.6f\n", theWindow->dX, theWindow->dY); // for debug
}
