#include "Window.h"

int Window::initialize()
{
	if (!glfwInit())
	{
		std::cerr << "GLFW library load failed...\n";
		glfwTerminate();
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

	glfwMakeContextCurrent(mainWindow);

	glfwSetFramebufferSizeCallback(mainWindow, handleFramebuffer);
	glfwSetCursorPosCallback(mainWindow, handleMouse);
	glfwSetScrollCallback(mainWindow, handleScroll);

	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Отключаем курсор в окне чтобы можно было плавать в любом направлении.

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glEnable(GL_DEPTH_TEST);

	// Setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	// указатель пользователя указывает на наш класс Window, чтобы можно было вызвать обработчик клавиш handleKeyboard при их нажатии.
	glfwSetWindowUserPointer(mainWindow, reinterpret_cast<void*>(this));

	return 0;
}

void Window::pollTime()
{
	float currentFrame = glfwGetTime();

	// per-frame time logic
	dT = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	static glm::vec2 lastXY;

	if (theWindow->mouseFirstMoved)
	{
		lastXY = glm::vec2(xPos,yPos);
		theWindow->mouseFirstMoved = false;
	}

	// reversed since y-coordinates go from bottom to top
	theWindow->dXdY = glm::vec2(xPos - lastXY.x, lastXY.y - yPos);
	lastXY = glm::vec2(xPos, yPos);
}

void Window::handleScroll(GLFWwindow* window, double nothing, double scroll)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));	

	theWindow->dScroll = scroll;

}
