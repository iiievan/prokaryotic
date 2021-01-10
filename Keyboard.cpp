#include "Keyboard.h"

std::vector<Keyboard*> Keyboard::_instances;

void Keyboard::callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	static GLboolean wireframe{ GL_FALSE }; // для отображения режима каркаса.

	// Send key event to all Keyboard instances
	for (Keyboard* Keyboard : _instances)
	{
		Keyboard->setIsKeyDown(key, action);
	}

	if (key == GLFW_KEY_UP && action != GLFW_RELEASE)
	{
		if (theWindow->alpha < 1.0)
			theWindow->alpha += 0.05;
	}
	if (key == GLFW_KEY_DOWN && action != GLFW_RELEASE)
	{
		if (theWindow->alpha > 0.0)
			theWindow->alpha -= 0.05;
	}

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