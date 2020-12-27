#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma once

// Window dimensions
#define WWIDTH	800 
#define WHEIGHT	600

class Window
{
public:
			Window(GLint windowWidth = WWIDTH, GLint windowHeight = WHEIGHT) 
		    : width(windowWidth), height(windowHeight) {}

	     int initialize();		
	   GLint getBufferWidth()	{ return bufferWidth; }
	   GLint getBufferHeight()	{ return bufferHeight; }
		bool getShouldClose()	{ return glfwWindowShouldClose(mainWindow); }
		void swapBuffers()		{ glfwSwapBuffers(mainWindow); }

			~Window()
			{
				glfwDestroyWindow(mainWindow);
				glfwTerminate();
			}


private:
	GLFWwindow* mainWindow	{nullptr};
		 GLint	width, height;
		 GLint	bufferWidth { 0 }, bufferHeight {0};
};