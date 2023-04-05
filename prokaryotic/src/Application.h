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
#include"scene/Scene_object.h"
#include"renderer/Renderer.h"
#include"camera/Camera.h"

#define STB_IMAGE_IMPLEMENTATION

namespace PROKARYOTIC
{
	constexpr unsigned WINDOW_WIDTH = 1024;
	constexpr unsigned WINDOW_HEIGHT = 768;

	class PRKRTC_API Application
	{
	public:
		  Camera  main_camera;

	public:
			        Application();
		   virtual ~Application();

	   GLFWwindow* init();

		     void  run();
		     void  process_input(GLFWwindow* window);

	private:
		GLFWwindow* m_Window;
		     float  m_alpha  { 0.2f };
		      bool  m_mirror  { false };
			  float  m_last_frame {0.0f};
			  float  m_dt {0.0f};

static Application* s_Instance;
	};

	// To be defined in client;
	Application* Create_application();

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);	
}


