#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <filesystem>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define VSHADER_LIGHT_PATH  "shaders/vertex_light.glsl"
#define FSHADER_LIGHT_PATH  "shaders/fragment_light.glsl"
#define VSHADER_CUBE_PATH   "shaders/vertex_cube.glsl"
#define FSHADER_CUBE_PATH   "shaders/fragment_cube.glsl"

unsigned int loadTexture(const char* path);
