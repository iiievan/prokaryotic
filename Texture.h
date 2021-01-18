#pragma once

#include <GL/glew.h>
#include <stb_image.h>

class Texture
{
public:
				Texture()					 { fileLocation = ""; }
				Texture(const char* fileloc) { fileLocation = fileloc; }
			   ~Texture()				     { clearTexture(); }

		void	loadTexture();
		void	useTexture();
		void	clearTexture();
			   
private:
	GLuint	textureID{ 0 };
		   int	width{ 0 };
		   int	height{ 0 };
		   int	bitDept{ 0 };
	const char* fileLocation;
};

