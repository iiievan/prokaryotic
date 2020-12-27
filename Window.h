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
			 	: width(windowWidth), height(windowHeight)
			 {}

	     int initialize();		
	   GLint getBufferWidth()	{ return bufferWidth; }
	   GLint getBufferHeight()	{ return bufferHeight; }
		bool getShouldClose()	{ return glfwWindowShouldClose(mainWindow); }
		void swapBuffers()		{ glfwSwapBuffers(mainWindow); }

	   bool* getsKeys()			{ return keys; }
	GLfloat  get_dX();
	GLfloat  get_dY();


			~Window()
			{
				glfwDestroyWindow(mainWindow);
				glfwTerminate();
			}


private:
	GLFWwindow* mainWindow	{nullptr};
		 GLint	width, height;
		 GLint	bufferWidth { 0 }, bufferHeight {0};

		 bool	keys[1024] {0};

	   GLfloat  lastX;
	   GLfloat  lastY;
	   GLfloat  dX;
	   GLfloat  dY;
	      bool  mouseFirstMoved;
   
	      void	createCallbacks();
   static void	handleKeyboard(GLFWwindow *window, int key, int code, int action, int mode);
   static void	handleMouse(GLFWwindow* window, double xPos, double yPos);
};