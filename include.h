#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//window dimensions
#define SCR_WIDTH	(800)
#define SCR_HEIGHT	(600)

#define VSHADER_PATH  "shaders/vertex.shader"
#define FSHADER_PATH  "shaders/fragment.shader"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, int key, int scancode, int action, int mods);