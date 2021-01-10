

#ifndef _WINDOW_H
#define _WINDOW_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Camera.h"

//window dimensions
#define SCR_WIDTH	(1366)
#define SCR_HEIGHT	(768)

class Window
{
public:
					Window(GLint windowWidth = SCR_WIDTH, GLint windowHeight = SCR_HEIGHT)
					: width(windowWidth), height(windowHeight), dXdY(0.0f,0.0f)
					{ }

			       ~Window()
			        {
						glfwDestroyWindow(mainWindow);
			        	glfwTerminate();
			        }

	         int	initialize();
	       GLint	getBufferWidth()	const { return bufferWidth; }
	       GLint	getBufferHeight()	const { return bufferHeight; }
	        bool	getShouldClose()	const { return glfwWindowShouldClose(mainWindow); }
		    void	swapBuffers()			  { glfwSwapBuffers(mainWindow); }
     GLFWwindow*	getWindow()				  { return mainWindow; }
		   float	getDeltaT()			const { return dT; }

	   glm::vec2	get_dXdY()			
					{ 
						glm::vec2 result = dXdY;
						dXdY = glm::vec2(0.0f, 0.0f);
						return result;
					}
		   float	get_dScroll()			 
					{ 
						float result = dScroll;
						dScroll = 0.0;
						return result; 
					}

	        void	pollTime();

		  float		alpha{ 0.2 };	// альфа канал одной из текстур

private:
	  GLFWwindow   *mainWindow { nullptr };

		   GLint	width, height;
	       GLint	bufferWidth { 0 }, bufferHeight { 0 };

	   glm::vec2	dXdY;
		   float	dScroll { 0.0f };
		    bool	mouseFirstMoved { true };

		   // timing
		  float		dT			{ 0.0f };	// time between current frame and last frame
		  float		lastFrame	{ 0.0f };



	static void		handleFramebuffer(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }

	static void		handleMouse(GLFWwindow* window, double xPos, double yPos);
	static void		handleScroll(GLFWwindow* window, double nothing, double scroll);
};
#endif // _WINDOW_H
