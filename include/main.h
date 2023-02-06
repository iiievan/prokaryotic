#ifndef __MAIN_H
#define __MAIN_H

#include <string>
#include <iostream>

#include<GLAD/glad.h>
#include<GLFW/glfw3.h>
#include<glm\glm.hpp> 

#include"shader/Shader.h"
#include"shader/Shader_program.h"
#include"mesh/Mesh.h"
#include"mesh/Vertex.h"
#include"mesh/Texture.h"
#include"mesh/Texture_loader.h"

#define STB_IMAGE_IMPLEMENTATION


void processInput(GLFWwindow* window);

#endif //__MAIN_H
