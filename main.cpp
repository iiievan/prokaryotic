#include "include.h"
#include "Window.h"
#include "Keyboard.h"
#include "Shader.h"
#include "Camera.h"

   Window	mainWindow;
 Keyboard	keyboard;
   Camera	camera(glm::vec3(0.0f, 0.0f, 3.0f));

glm::vec3	lightPos(1.2f, 1.0f, 2.0f);

int main()
{
	unsigned int VBO, lightVAO, cubeVAO;
	unsigned int texture1, texture2;
	int width, height, nrChannels;
	unsigned char* data;
	
	float vertices[] =
	{
		// positions          // normals           // texture coords
		 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		  0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		 -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		  0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		 -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		 -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		  0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		  0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		  0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		 -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		 -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		  0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		 -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	glm::vec3 cubePositions[] =
	{
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	mainWindow.initialize();
	keyboard.setInputWindow(&mainWindow);

	// Шейдер создаем ПОСЛЕ создания окна и контекста окна.
	Shader lightShader(VSHADER_LIGHT_PATH  , FSHADER_LIGHT_PATH);
	Shader cubeShader(VSHADER_CUBE_PATH, FSHADER_CUBE_PATH);

	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);	

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(cubeVAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	// load textures
// -----------------------------------------------------------------------------
	unsigned int diffuseMap = loadTexture("textures/container2.png");
	unsigned int specularMap = loadTexture("textures/container2_specular_map.png");
	unsigned int emissionMap = loadTexture("textures/container2_emissive.png");

	// shader configuration
	// --------------------
	cubeShader.use();
	cubeShader.setInt("material.diffuse",  0);
	cubeShader.setInt("material.specular", 1);
	cubeShader.setInt("material.emission", 2);

	while (!mainWindow.getShouldClose())
	{
		/* Обработка клавиш c антидребезгом происходит в  debInput*/
		mainWindow.pollTime();
		camera.keyControl(keyboard.getKeys(), mainWindow.getDeltaT());
		camera.mouseControl(mainWindow.get_dXdY());
		camera.zoomControl(mainWindow.get_dScroll());

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//render ---------------------------->	

		// bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, emissionMap);

		cubeShader.use();
		//cubeShader.setVec3("light.position", lightPos);
		cubeShader.setVec3("light.direction", -0.2f,-1.0f,-0.3f);
		cubeShader.setVec3("viewPos", camera.Position);

		cubeShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
		cubeShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
		cubeShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

		cubeShader.setFloat("light.constant", 1.0f);
		cubeShader.setFloat("light.linear", 0.09f);
		cubeShader.setFloat("light.quadratic", 0.032f);

		cubeShader.setFloat("material.shininess", 64.0f);	


		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 cubeModel = glm::mat4(1.0f);
		cubeShader.setMat4("projection", projection);
		cubeShader.setMat4("view", view);
		//cubeShader.setMat4("model", cubeModel);
		
		glBindVertexArray(cubeVAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			cubeModel = glm::mat4(1.0f);
			cubeModel = glm::translate(cubeModel, cubePositions[i]);
			float angle = glm::radians(30.0f * i) * (float)glfwGetTime();
			cubeModel = glm::rotate(cubeModel, angle, glm::vec3(1.0f, 0.3f, 0.5f));
			cubeShader.setMat4("model", cubeModel);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		lightShader.use();
		lightShader.setMat4("projection", projection);
		lightShader.setMat4("view", view);
		glm::mat4 lightModel = glm::mat4(1.0f);
		lightModel = glm::translate(lightModel, lightPos);
		lightModel = glm::scale(lightModel, glm::vec3(0.2f));
		lightShader.setMat4("model", lightModel);
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//<---------------------------- render

		mainWindow.swapBuffers();
		glfwPollEvents();
	}

	// deallocate all resources
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteBuffers(1, &VBO);
	
	glfwTerminate();
	return 0;
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

