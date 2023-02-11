#ifndef __MAIN_H
#define __MAIN_H

#include <string>
#include <iostream>

#include<GLAD/glad.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"shader/Shader.h"
#include"shader/Shader_program.h"
#include"model/Mesh.h"
#include"model/Vertex.h"
#include"model/Texture.h"
#include"model/Texture_loader.h"
#include"model/Material.h"
#include"scene/Scene_object.h"
#include"renderer/Renderer.h"

#define STB_IMAGE_IMPLEMENTATION


void processInput(GLFWwindow* window);

#endif //__MAIN_H
