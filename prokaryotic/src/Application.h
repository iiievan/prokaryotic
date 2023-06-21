#pragma once

#include "Core.h"

#include <string>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include<GLAD/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "Log.h"

#include"shader/Shader.h"
#include"shader/Shader_program.h"
#include"model/Mesh.h"
#include"model/Vertex.h"
#include"model/Texture.h"
#include"model/Texture_loader.h"
#include"model/Material.h"
#include"model/meshes/Cube.h"
#include"userinterface/UI_item.h"
#include"scene/Scene_object.h"
#include"renderer/Renderer.h"
#include"camera/Camera.h"
#include "light/Light_source.h"

#include "utils/Frame_buffer.h"

#define STB_IMAGE_IMPLEMENTATION

namespace PROKARYOTIC
{
	constexpr unsigned WINDOW_WIDTH = 1920;
	constexpr unsigned WINDOW_HEIGHT = 1080;

	class PRKRTC_API Application
	{
	public:
			        Application();
		   virtual ~Application();

	   GLFWwindow* init();

		     void  run();
		     void  process_input(GLFWwindow* window);

	private:
		inline   bool  m_should_quit() const	{ return glfwWindowShouldClose(m_Window); }
		inline   void  m_poll()					{ glfwPollEvents(); }
		inline   void  m_swap_buffers()			{ glfwSwapBuffers(m_Window); }
		inline double  m_get_time() const		{ return static_cast<double>(glfwGetTime()); }
		inline   void  m_transparency(bool state)
		{
			if (state) 
			{
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}
			else 
				glDisable(GL_BLEND);

		}

		inline   void  m_depth_test(bool state)
		{
			if (state)
				glEnable(GL_DEPTH_TEST);
			else
				glDisable(GL_DEPTH_TEST);
		}

		inline   void  m_cull(int state)
		{
			switch (state) 
			{
			case GL_FRONT:
				glEnable(GL_CULL_FACE);
				glCullFace(GL_FRONT);
				glFrontFace(GL_CCW);
				break;
			case GL_BACK:
				glEnable(GL_CULL_FACE);
				glCullFace(GL_BACK);
				glFrontFace(GL_CCW);
				break;
			default:
				glDisable(GL_CULL_FACE);
				break;
			}
		}

		inline    void  m_wirefreame(bool state) 
		{
			if (state)
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}


		GLFWwindow*  m_Window;
	   Frame_buffer  m_screen;
			  float  m_last_frame {0.0f};
			  float  m_dt {0.0f};

static Application* s_Instance;
	};

	// To be defined in client;
	Application* Create_application();

	void  deb_input(GLFWwindow* window, int key, int scancode, int action, int mods);
	void  mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void  scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void  framebuffer_size_callback(GLFWwindow* window, int width, int height);	
	void  handle_gui(UI_item& ui_obj, Camera* p_camera);
}


